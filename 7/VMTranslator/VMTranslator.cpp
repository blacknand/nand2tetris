#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"
#include "Parser.h"


int main(int argc, char **argv) {
    Parser parser;
    CodeWriter codeWriter;

    std::string vmFileName = argv[1];
    std::size_t vmExtensionI = vmFileName.find(".vm");
    std::size_t forwardSlash = vmFileName.find_last_of("/");

    if (forwardSlash != std::string::npos) {
        std::string strippedFileName = vmFileName.substr((forwardSlash + 1));
        std::size_t fileExtension = strippedFileName.find(".vm");
        strippedFileName.erase(fileExtension);
        vmFileName = strippedFileName;
    }
    else
        vmFileName.erase(vmExtensionI, 3);

    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    std::vector<std::vector<std::string>> fileVect = parser.getFileVect();
    codeWriter.initializer((vmFileName + ".asm").c_str(), vmFileName);

    for (int i = 0; i < fileVect.size(); i++) {
        for (int j = 0; j < fileVect[i].size(); j++) {
            std::cout << fileVect[i][j] << std::endl;
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
    return 0;
}