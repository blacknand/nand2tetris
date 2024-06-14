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

    std::string asmFileName = argv[0];
    int asmFileNamePos = asmFileName.find_first_not_of("./");
    asmFileName = asmFileName.substr(asmFileNamePos) + ".asm";

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

    // TODO: VM translator
    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    std::vector<std::vector<std::string>> fileVect = parser.getFileVect();
    codeWriter.initializer(asmFileName.c_str(), vmFileName);

    for (int i = 0; i < fileVect.size(); i++) {
        for (int j = 0; j < fileVect[i].size(); j++) {
            if (parser.hasMoreLines()) {
                parser.advance();
                std::string arg1 = "NULL", arg2 = "NULL";
                const std::string commandType = parser.commandType();
                if (commandType != "C_RETURN")
                    arg1 = parser.arg1();
                else if (commandType == "C_PUSH" || commandType == "C_POP" || commandType == "C_FUNCTION"
                        || commandType == "C_CALL")
                    arg2 = parser.arg2();
                
                std::cout << "fileVect[" << i << "]" << "[" << j << "]" << " " << "arg1: " << arg1 << std::endl;
                std::cout << "fileVect[" << i << "]" << "[" << j << "]" << " " << "arg2: " << arg2 << std::endl;
                // if (commandType == "C_ARITHMETIC")
                //     codeWriter.writeArithmetic(arg1);
                // else if (arg2 != "NULL") 
                //     codeWriter.writePushPop()
            }
        }
    }
    codeWriter.close();
    return 0;
}