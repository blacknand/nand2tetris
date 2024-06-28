#include <string>
#include <cstring>
#include <vector>
#include "JackTokenizer.h"


JackTokenizer::initializer(const char *inputFile) {
    std::string line;
    std::ifstream jackFile(inputFile);
    
    if (jackFile.is_open()) {
        while (getline(jackFile, line)) {
            std::vector<std::string> singleLine;
            singleLine.push_back(line);
            lineVect.push_back(singleLine);
        }
        jackFile.close();
    }
}


