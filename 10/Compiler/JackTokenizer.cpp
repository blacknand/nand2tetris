#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim.hpp>
#include "JackTokenizer.h"


// Define static class members to be allocated
// std::vector<std::vector<std::string>> JackTokenizer::tokenizedVec;
// int JackTokenizer::currentLine = 0;
// int JackTokenizer::currentToken = 0;
// std::string JackTokenizer::currentToken;
// JackTokenizer::currentIndex = 0;


void JackTokenizer::initializer(std::string inputFile) {
    // Tokenizes input file and adds tokens to 2d vector
    std::string line;
    std::ifstream jackFile(inputFile);
    bool flag = false;
    int lineIndex = 0, tokenIndex = 0;

    if (jackFile.is_open()) {
        while (getline(jackFile, line)) {
            std::size_t foundWhiteSpace = line.find_first_not_of(" \t\n\v\f\r");
            if (foundWhiteSpace != std::string::npos) {
                std::size_t startComment = line.find("/*");
                std::size_t endComment = line.find("*/");
                std::size_t startAPIcomment = line.find("/**");
                std::size_t lastNonWhiteSpace = line.find_last_not_of(" \t\n\v\f\r");

                if (!flag) {
                    // Check if in comment
                    if (startComment != std::string::npos)
                        flag = true;
                    else if (line.substr(foundWhiteSpace, 2) == "//")
                        continue;
                    else if (startAPIcomment != std::string::npos)
                        flag = true;
                }

                if (flag) {
                    if (endComment != std::string::npos) {
                        flag = false;
                        continue;
                    } else
                        continue;
                } 

                if (!flag) {
                    std::string token;
                    tokenIndex = 0;                             // Reset token index for new valid line
                    // Tokenize
                    for (char c : line) {
                        if (!isspace(c))
                            token += c;
                        else if (!token.empty()) {
                            tokens.push_back({token, lineIndex, tokenIndex});
                            token.clear();
                            tokenIndex++;
                        }
                    }

                    // Edge case to ensure last token is added
                    if (!token.empty()) {
                        tokens.push_back({token, lineIndex, tokenIndex});
                        tokenIndex++;
                    }

                    lineIndex++;
                }
            }
        }
    }
}


bool JackTokenizer::hasMoreTokens() {
    return currentIndex < tokens.size();
}


void JackTokenizer::advance() {
    currentToken = tokens[currentIndex].token;
    currentIndex++;
}


const std::vector<JackTokenizer::Token>& JackTokenizer::getTokens() const {
    return tokens;
}