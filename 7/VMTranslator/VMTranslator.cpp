// Translates Hack VM bytecode into Hack ASM

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
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
    const char *testFile = argv[1];
    codeWriter.initializer(testFile);
    return 1;
}