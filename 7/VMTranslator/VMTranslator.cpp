#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "CodeWriter.h"
#include "FileOp.h"
#include "Parser.h"


int main(int argc, char **argv) {
    Parser parser;
    CodeWriter codeWriter;

    bool directory = false;
    std::string dirFile;
    std::vector<std::vector<std::string>> vmFiles;
    std::string vmFileName = argv[1];
    std::size_t vmExtensionI = vmFileName.find(".vm");
    std::size_t forwardSlash = vmFileName.find_last_of("/");

    // Is a forward slash and is a single file
    if (forwardSlash != std::string::npos && vmExtensionI != std::string::npos) {
        std::string strippedFileName = vmFileName.substr((forwardSlash + 1));
        std::size_t fileExtension = strippedFileName.find(".vm");
        strippedFileName.erase(fileExtension);
        vmFileName = strippedFileName;
    // Is no forward slash and is a single file
    } else if (forwardSlash == std::string::npos && vmExtensionI != std::string::npos)
        vmFileName.erase(vmExtensionI, 3);
    else if (vmExtensionI == std::string::npos)
        directory = true;

    if (directory) {
        using recursive_dir_iter = std::filesystem::recursive_directory_iterator;

        for (const auto &dirEntry: recursive_dir_iter(argv[1])) {
            if (dirEntry.is_regular_file() && dirEntry.path().extension() == ".vm") {
                // Make sure Sys.vm is translated before any other .vm files, and Main.vm translated second
                if (dirEntry.path().stem().string() == "Sys")
                    vmFiles.insert(vmFiles.begin(), {dirEntry.path().string(), dirEntry.path().stem().string()});
                // else if (dirEntry.path().stem().string() == "Main")
                //     vmFiles.insert(vmFiles.begin() + 1, {dirEntry.path().string(), dirEntry.path().stem().string()});
                else
                    vmFiles.push_back({dirEntry.path().string(), dirEntry.path().stem().string()});
            }
        }
        std::filesystem::path abs_path(vmFileName);
        std::string finalDir;

        if (abs_path.has_filename())
            finalDir = abs_path.filename().string();
        else 
            finalDir = abs_path.parent_path().filename().string();

        finalDir = finalDir + ".asm";
        codeWriter.initializer(finalDir.c_str());
    } else {
        std::string strArgv = argv[1];
        vmFiles.push_back({strArgv, vmFileName});
        codeWriter.initializer((vmFileName + ".asm").c_str());
    }

    for (int k = 0; k < vmFiles.size(); k++) {
        std::ifstream inputFile;

        if (directory) 
            inputFile.open(vmFiles.at(k).at(0));
        else
            inputFile.open(argv[1]);

        codeWriter.setFileName(vmFiles.at(k).at(1));
        parser.initializer(inputFile);
        std::vector<std::vector<std::string>> fileVect = parser.getFileVect();

        for (int i = 0; i < fileVect.size(); i++) {
            for (int j = 0; j < fileVect[i].size(); j++) {
                if (parser.hasMoreLines()) {
                    parser.advance();
                    std::string arg1;
                    int arg2;
                    std::string commandType = parser.commandType();

                    if (commandType != "C_RETURN")
                        arg1 = parser.arg1();
                    if (commandType == "C_PUSH" || commandType == "C_POP"
                        || commandType == "C_FUNCTION" || commandType == "C_CALL")
                        arg2 = parser.arg2();

                    codeWriter.writeDebugMarker();
                    if (commandType == "C_ARITHMETIC")
                        codeWriter.writeArithmetic(arg1);
                    else if (commandType == "C_PUSH" || commandType == "C_POP")
                        codeWriter.writePushPop(commandType, arg1, arg2);
                    else if (commandType == "C_LABEL")
                        codeWriter.writeLabel(arg1);
                    else if (commandType == "C_GOTO")
                        codeWriter.writeGoto(arg1);
                    else if (commandType == "C_IF")
                        codeWriter.writeIf(arg1);
                    else if (commandType == "C_CALL")
                        codeWriter.writeCall(arg1, arg2);
                    else if (commandType == "C_FUNCTION")
                        codeWriter.writeFunction(arg1, arg2);
                    else if (commandType == "C_RETURN")
                        codeWriter.writeReturn();
                }
            }
        }
    }
    codeWriter.close();
    return 0;
}