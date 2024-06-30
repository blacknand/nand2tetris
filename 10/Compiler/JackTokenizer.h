#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef JACK_TOKENIZER
#define JACK_TOKENIZER

class JackTokenizer {
    public:
        struct Token {
            std::string token;
            int lineIndex;
            int tokenIndex;
        };
        enum TokenElements {
            KEYWORD = 1,
            SYMBOL,
            INT_CONST,
            STR_CONST,
            IDENTIFIER
        };
    private:
        std::vector<Token> tokens;
        int currentIndex = 0;
        std::string currentToken;
        static const std::unordered_map<std::string, TokenElements> keywordMap;
        static const std::unordered_map<char, TokenElements> symbolMap;
    public:
        void initializer(std::string inputFile);
        bool hasMoreTokens();
        void advance();
        const TokenElements tokenType();
        const std::string &tokenElements();
        const std::string &keyWord();
        char symbol();
        std::string identifier();
        int intVal();
        std::string stringVal();
        const std::vector<Token>& getTokens() const;
};

#endif      // JACK_TOKENIZER