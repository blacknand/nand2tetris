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
    int iterations = 0;
    std::string dirFile;
    std::vector<std::pair<std::string, std::string>> vmFiles;
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
                std::string strippedFileName = dirEntry.path().stem().string();
                std::pair<std::string, std::string> linePair = {strippedFileName, dirEntry.path().string()};
                vmFiles.push_back(linePair);
                iterations++;
            }
        }
    } else {
        iterations = 1;
        vmFiles.push_back({vmFileName, argv[1]});
    }

    for (int k = 0; k < iterations; k++) {
        std::ifstream inputFile;
        if (directory)
            inputFile.open(vmFiles.at(k).second);
        else
            inputFile.open(argv[1]);
        parser.initializer(inputFile);
        std::vector<std::vector<std::string>> fileVect = parser.getFileVect();
        codeWriter.initializer((vmFiles.at(k).first + ".asm").c_str(), vmFiles.at(k).first);

        for (int i = 0; i < fileVect.size(); i++) {
            for (int j = 0; j < fileVect[i].size(); j++) {
                if (parser.hasMoreLines()) {
                    parser.advance();
                    std::string arg1;
                    int arg2;
                    std::string commandType = parser.commandType();
                    if (commandType != "C_RETURN")
                        arg1 = parser.arg1();
                    if (commandType == "C_PUSH" || commandType == "C_POP")
                        arg2 = parser.arg2();

                    if (commandType == "C_ARITHMETIC")
                        codeWriter.writeArithmetic(arg1);
                    else if (commandType == "C_PUSH" || commandType == "C_POP")
                        codeWriter.writePushPop(commandType, arg1, arg2);
                }
            }
        }
        codeWriter.close();
    }
    return 0;
}