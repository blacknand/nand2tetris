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
    codeWriter.initializer(asmFileName.c_str());
    codeWriter.writeArithmetic("neg");
    codeWriter.close();
    return 1;
}