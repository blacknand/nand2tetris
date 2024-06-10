#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
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
            boost::algorithm::trim(line);
            lineVect.push_back(line);
            fileVect.push_back(lineVect);
        }
        inputFile.close();
        return;
    }
    std::cout << "Failed to open file" << std::endl;
}

bool Parser::hasMoreLines() {
    int iter = (currentLine > 0) ? (currentLine + 1) : 0;

    for (int i = iter; i < fileVect.size(); i++) {
        for (int j = 0; j < fileVect[i].size(); j++) {
            std::size_t foundWhiteSpace = fileVect[i][j].find_first_not_of(" \t\n\v\f\r");
            if (fileVect[i][j].substr(foundWhiteSpace, 2) != "//")
                return true;
            continue;
        }
    }

    return false;
}