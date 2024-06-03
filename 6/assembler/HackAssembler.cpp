/*
    Implementation of an assembler for the Hack computer. Converts Hack
    assembly language code into binary code and generates a .hack file.

    The assembler does not perform error checking of any kind and it is 
    assumed that the assembley code is error free.
*/


#include <cctype>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "HackAssembler.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./HackAssembler prog.asm" << std::endl;
        return 1;
    }

    Parser parser;
    parser.initializer(argv[1]);
    parser.advance();
    std::vector<std::vector<std::string>> lineVect = parser.getVect();
    std::string currentInstruction = parser.getCurrentInstruct();
    int currentLine = parser.getCurrentLine();
    std::cout << currentInstruction << std::endl;
    std::cout << currentLine << std::endl;
    parser.advance();

    currentInstruction = parser.getCurrentInstruct();
    currentLine = parser.getCurrentLine();
    std::cout << currentInstruction << std::endl;
    std::cout << currentLine << std::endl;

    return 0;
}


void Parser::initializer(std::string inputFile) {
    // Open .asm file and read into a 2d vector to be operated on
    std::string line;
    std::ifstream asmFile(inputFile);
    if (asmFile.is_open()) {
        while (getline(asmFile, line)) {
            std::vector<std::string> singleLine;
            singleLine.push_back(line);
            lineVect.push_back(singleLine);
        }
        asmFile.close();
    } else
        std::cout << "Failed to open " << inputFile << std::endl;
}


bool Parser::hasMoreLines() {
    // Returns if there are any more valid lines (i.e. not a comment line)
    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::size_t foundWhiteSpace = lineVect[i][j].find_first_not_of(' ');
            if (foundWhiteSpace != std::string::npos) {
                if (lineVect[i][j].substr(foundWhiteSpace, 2) != "//")
                    return true;
                else
                    continue;
            }
        }
    }

    return false;
}


void Parser::advance() {
    // Reads the next instruction from input and makes current instruction
    int iter;
    if (currentLine > 0) {
        iter = currentLine;
        iter++;
    } else
        iter = 0;

    for (int i = iter; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::size_t foundWhiteSpace = lineVect[i][j].find_first_not_of(' ');
            if (foundWhiteSpace != std::string::npos) {
                if (lineVect[i][j].substr(foundWhiteSpace, 2) != "//") {
                    currentLine = i;
                    currentInstruction = lineVect[i][j];
                    return;
                } else    
                    continue;
            }
        }
    }

}


const std::string Parser::instructionType() {
    return "fuck";
}


std::string Parser::symbol() {
    return "fuck";
}


std::string Parser::dest() {
    return "fuck";
}


std::string Parser::comp() {
    return "fuck";
}


std::string Parser::jump() {
    return "fuck";
}