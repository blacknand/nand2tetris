#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "VMTranslator.h"

int main(int argc, char **argv) {
    Parser parser;
    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    parser.getFileVect();
    return 1;
}

void Parser::initializer(std::ifstream &inputFile) {
    std::string line;
    std::vector<std::string> lineVect;
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            lineVect.clear();
            lineVect.push_back(line);
            fileVect.push_back(lineVect);
        }
        inputFile.close();
        return;
    }
    std::cout << "Failed to open file" << std::endl;
}