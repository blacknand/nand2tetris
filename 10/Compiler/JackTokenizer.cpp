#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <boost/algorithm/string/trim.hpp>
#include "JackTokenizer.h"


// Define static class members to be allocated
const std::unordered_map<std::string, JackTokenizer::TokenElements> JackTokenizer::keywordMap = {
    {"class", TokenElements::KEYWORD}, {"constructor", TokenElements::KEYWORD}, {"function", TokenElements::KEYWORD},
    {"method", TokenElements::KEYWORD}, {"field", TokenElements::KEYWORD}, {"static", TokenElements::KEYWORD},
    {"var", TokenElements::KEYWORD}, {"int", TokenElements::KEYWORD}, {"char", TokenElements::KEYWORD},
    {"boolean", TokenElements::KEYWORD}, {"void", TokenElements::KEYWORD}, {"true", TokenElements::KEYWORD},
    {"false", TokenElements::KEYWORD}, {"null", TokenElements::KEYWORD}, {"this", TokenElements::KEYWORD},
    {"let", TokenElements::KEYWORD}, {"do", TokenElements::KEYWORD}, {"if", TokenElements::KEYWORD},
    {"else", TokenElements::KEYWORD}, {"while", TokenElements::KEYWORD}, {"return", TokenElements::KEYWORD}
};

const std::unordered_map<char, JackTokenizer::TokenElements> JackTokenizer::symbolMap = {
    {'{', TokenElements::SYMBOL}, {'}', TokenElements::SYMBOL}, {'(', TokenElements::SYMBOL}, {')', TokenElements::SYMBOL},
    {'[', TokenElements::SYMBOL}, {']', TokenElements::SYMBOL}, {'.', TokenElements::SYMBOL}, {',', TokenElements::SYMBOL},
    {';', TokenElements::SYMBOL}, {'+', TokenElements::SYMBOL}, {'-', TokenElements::SYMBOL}, {'*', TokenElements::SYMBOL},
    {'/', TokenElements::SYMBOL}, {'&', TokenElements::SYMBOL}, {'|', TokenElements::SYMBOL}, {'<', TokenElements::SYMBOL},
    {'>', TokenElements::SYMBOL}, {'=', TokenElements::SYMBOL}, {'~', TokenElements::SYMBOL}
};


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

                std::size_t inlineCommentPos = line.find("//");
                if (inlineCommentPos != std::string::npos)
                    line.erase(inlineCommentPos);

                std::string token;
                tokenIndex = 0;                             // Reset token index for new valid line

                for (std::size_t i = 0; i < line.length(); i++) {
                    char c = line[i];
                    if (isspace(c)) {
                        if (!token.empty()) {
                            tokens.push_back({token, lineIndex, tokenIndex});
                            token.clear();
                            tokenIndex++;
                        }
                    } else if (ispunct(c)) {
                        if (!token.empty()) {
                            tokens.push_back({token, lineIndex, tokenIndex});
                            token.clear();
                            tokenIndex++;
                        }
                        tokens.push_back({std::string(1, c), lineIndex, tokenIndex});
                        tokenIndex++;
                    } else
                        token += c;
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


bool JackTokenizer::hasMoreTokens() {
    return currentIndex < tokens.size();
}


void JackTokenizer::advance() {
    currentToken = tokens[currentIndex].token;
    std::cout << currentToken << std::endl;
    currentIndex++;
}


const JackTokenizer::TokenElements JackTokenizer::tokenType() {
    std::unordered_map<std::string, TokenElements>::const_iterator keywordCode = keywordMap.find(currentToken);
    std::unordered_map<char, TokenElements>::const_iterator symbolCode = symbolMap.find(currentToken[0]);
    if (keywordCode != keywordMap.end())
        return keywordCode->second;
    else if (symbolCode != symbolMap.end())
        return symbolCode->second;
    else if (std::regex_match(currentToken, std::regex("[a-zA-Z_][a-zA-Z0-9_]*")))
        return TokenElements::IDENTIFIER;
    else if (std::regex_match(currentToken, std::regex("[0-9]+")))
        return TokenElements::INT_CONST;
    else if (std::regex_match(currentToken, std::regex("\".*\"")))
        return TokenElements::STR_CONST;
}


const std::vector<JackTokenizer::Token>& JackTokenizer::getTokens() const {
    return tokens;
}