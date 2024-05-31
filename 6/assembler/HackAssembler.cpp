// Converts hack assembly language into binary

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "HackAssembler.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./HackAssembler prog.asm" << std::endl;
        return 1;
    }

    Parser parser;
    parser.setLineCount(0);
    parser.setCurrentLine(0);

    parser.initializer(argv[1]);

    return 0;
}

void Parser::initializer(std::string inputFile) {
    std::string line;
    std::ifstream asmFile(inputFile);
    if (asmFile.is_open()) {
        while (getline(asmFile, line)) {
            std::cout << line << std::endl;
        }
        asmFile.close();
    } else 
        std::cout << "Failed to open " << inputFile << std::endl;
}

bool Parser::hasMoreLines(int lineCount, int currentLine) {
    if (currentLine > lineCount)
        return true;
    else
        return false;
}

void Parser::advance(int currentLine) {

}