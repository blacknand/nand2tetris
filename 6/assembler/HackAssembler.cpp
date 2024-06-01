// Converts hack assembly language into binary

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
    parser.hasMoreLines();
    std::vector<std::vector<std::string>> lineVect = parser.getVect();
    std::vector<std::vector<std::string>> strippedVect = parser.getStrippedVect();
    // for (int i = 0; i < lineVect.size(); i++) {
    //     for (int j = 0; j < lineVect[i].size(); j++) {
    //         std::cout << "lineVect[" << i << "]" << "[" << j << "]" << lineVect[i][j] << std::endl;
    //     }
    // }
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

    // for (int i = 0; i < lineVect.size(); i++) {
    //     for (int j = 0; j < lineVect[i].size(); j++) {
    //         std::vector<std::string> singleStrippedLine;
    //         std::string strippedString;
    //         for (auto c: lineVect[i][j]) {
    //             if (!isspace(c)) {
    //                 strippedString.push_back(c);
    //             }
    //         }
    //         if (strippedString.find_first_not_of(' ') != std::string::npos) {
    //             singleStrippedLine.push_back(strippedString);
    //             strippedVect.push_back(singleStrippedLine);
    //         }
    //     }
    // }

    // TODO: Need to erase any strippedVect[i][j] vectors that begin with '//'
    // for (int i = 0; i < strippedVect.size(); i++) {
    //     for (int j = 0; j < strippedVect[i].size(); j++) {
    //         if (strippedVect[i][j].substr(0, 2) == "//") {
    //             strippedVect.erase(strippedVect[i][j]);
    //         }
    //     }
    // }

    // for (vector<my_class>::reverse_iterator riter = my_vector.rbegin();
    //  riter != my_vector.rend(); ++riter) 

    // for (std::vector<std::vector<std::string>>::reverse_iterator riter = strippedVect.rbegin(); riter != strippedVect.rend(); riter++) {
    //     for (const std::string &innerRiter: *riter) {
    //         std::cout << innerRiter << std::endl;
    //     }
    // }
}

bool Parser::hasMoreLines() {

    // TODO: Needs to read and strip comments + whitespace and then return if it has found a line

    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::size_t foundWhiteSpace = lineVect[i][j].find_first_not_of(' ');

            if (foundWhiteSpace != std::string::npos) {
                if (lineVect[i][j].substr(foundWhiteSpace, foundWhiteSpace + 2) != "//")
                    return true;
                else 
                    return false;
            }
        }
    }

    return false;
}

void Parser::advance() {

}