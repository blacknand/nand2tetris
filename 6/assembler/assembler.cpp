#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "code.h"
#include "parser.h"
#include "symbolTable.h"

int main(int argc, char** argv) {
    Parser parser;
    parser.initializer(argv[1]);
    return 0;
}

void Parser::initializer(std::string file) {
    std::string line;
    std::ifstream asmFile(file);
    if (asmFile.is_open()) {
        while (getline(asmFile, line)) {
            std::cout << line << std::endl;
        }
        asmFile.close();
    } else 
        std::cout << "Unable to open file" << std::endl;
}