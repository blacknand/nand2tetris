#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim.hpp>
#include "JackTokenizer.h"

std::vector<std::vector<std::string>> JackTokenizer::tokenizedVec;
void JackTokenizer::initializer(std::string inputFile) {
    std::string line;
    std::ifstream jackFile(inputFile);
    bool flag = false;
    if (jackFile.is_open()) {
        while (getline(jackFile, line)) {
            std::size_t foundWhiteSpace = line.find_first_not_of(" \t\n\v\f\r");
            if (foundWhiteSpace != std::string::npos) {
                std::size_t startComment = line.find("/*");
                std::size_t endComment = line.find("*/");
                std::size_t startAPIcomment = line.find("/**");
                std::size_t lastNonWhiteSpace = line.find_last_not_of(" \t\n\v\f\r");

                if (!flag) {
                    if (startComment != std::string::npos)
                        flag = true;
                    else if (line.substr(foundWhiteSpace, 2) == "//")
                        continue;
                    else if (startAPIcomment != std::string::npos)
                        flag = true;
                }

                if (flag) {
                    // Is entering even when endComment is not on line
                    if (endComment != std::string::npos) {
                        flag = false;
                        continue;
                    } else
                        continue;
                } 

                if (!flag) {
                    std::vector<std::string> jackLine;
                    std::string token;

                    for (char c : line) {
                        if (!isspace(c))
                            token += c;
                        else if (!token.empty()) {
                            jackLine.push_back(token);
                            token.clear();
                        }
                    }

                    if (!token.empty()) 
                        jackLine.push_back(token);

                    tokenizedVec.push_back(jackLine);
                }
            }
        }
    }
}


bool JackTokenizer::hasMoreTokens() {

    return false;
}


void JackTokenizer::advance() {

}