// Translates Hack VM bytecode into Hack ASM

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "Parser.h"


int main(int argc, char **argv) {
    Parser parser;
    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    parser.getFileVect();
    parser.advance();
    parser.advance();
    parser.commandType();
    std::cout << parser.arg1() << std::endl;
    std::cout << parser.arg2() << std::endl;
    return 1;
}