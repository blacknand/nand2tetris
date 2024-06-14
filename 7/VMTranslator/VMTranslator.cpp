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
    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    parser.getFileVect();
    parser.advance();
    parser.commandType();

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

    codeWriter.initializer(asmFileName.c_str(), vmFileName);
    codeWriter.writeArithmetic("add");
    codeWriter.close();

    return 1;
}