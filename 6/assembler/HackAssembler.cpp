// Converts hack assembly language into binary

#include <cctype>
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
    std::vector<std::vector<std::string>> lineVect = parser.getVect();
    std::vector<std::vector<std::string>> strippedVect = parser.getStrippedVect();
    for (int i = 0; i < strippedVect.size(); i++) {
        for (int j = 0; j < strippedVect[i].size(); j++) {
            std::cout << "strippedVect[" << i << "]" << "[" << j << "]" << strippedVect[i][j] << std::endl;
        }
    }
    return 0;
}

void Parser::initializer(std::string inputFile) {
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

    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::vector<std::string> singleStrippedLine;
            std::string strippedString;
            for (auto c: lineVect[i][j]) {
                if (!isspace(c)) {
                    strippedString.push_back(c);
                }
            }
            if (strippedString.find_first_not_of(' ') != std::string::npos) {
                singleStrippedLine.push_back(strippedString);
                strippedVect.push_back(singleStrippedLine);
            }
        }
    }

    // TODO: Need to erase any strippedVect[i][j] vectors that begin with '//'
    for (int i = 0; i < strippedVect.size(); i++) {
        for (int j = 0; j < strippedVect[i].size(); j++) {
            if (strippedVect[i][j].substr(0, 2) == "//") {
                strippedVect[i].erase(strippedVect[i][j]);
            }
        }
    }
}

bool Parser::hasMoreLines(int lineCount, int currentLine) {
    if (currentLine > lineCount)
        return true;
    else
        return false;
}

void Parser::advance(int currentLine) {

}