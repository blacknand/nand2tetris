#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
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
    std::vector<std::string> vmFiles;
    std::string vmFileName = argv[1];
    std::size_t vmExtensionI = vmFileName.find(".vm");
    std::size_t forwardSlash = vmFileName.find_last_of("/");

    // TODO: Instead of translating each .vm file into a seperate .asm file,
    // the .vm files need to be translated into a single .vm file

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
                vmFiles.push_back(dirEntry.path().string());
            }
        }
    } else
        vmFiles.push_back(argv[1]);

    std::string testStrr = "test.asm";
    codeWriter.initializer(testStrr.c_str(), "test");
    for (int k = 0; k < vmFiles.size(); k++) {
        std::ifstream inputFile;
        if (directory)
            inputFile.open(vmFiles.at(k));
        else
            inputFile.open(argv[1]);
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
                        || commandType == "C_FUNCTION" || commandType == "C_RETURN")
                        arg2 = parser.arg2();

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
                }
            }
        }
    }
    codeWriter.close();
    return 0;
}