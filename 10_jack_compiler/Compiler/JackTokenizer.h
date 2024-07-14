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
            STRING_CONST,
            IDENTIFIER
        };
        enum KeywordElements {
            CLASS = 1,
            METHOD,
            FUNCTION,
            CONSTRUCTOR,
            INT,
            BOOLEAN,
            CHAR,
            VOID,
            VAR,
            STATIC,
            FIELD,
            LET,
            DO,
            IF,
            ELSE,
            WHILE,
            RETURN,
            TRUE,
            FALSE,
            JACK_NULL,
            THIS
        };
    private:
        static std::vector<Token> tokens;
        static int currentIndex;
        static std::string currentToken;
        static const std::unordered_map<std::string, TokenElements> keywordMap;
        static const std::unordered_map<char, TokenElements> symbolMap;
        static const std::unordered_map<std::string, KeywordElements> tokenKeywordMap;
        static int savedIndex;
    public:
        void initializer(std::string inputFile);
        bool hasMoreTokens();
        void advance();
        const TokenElements tokenType();
        const KeywordElements keyWord();
        const std::string symbol();
        const std::string identifier();
        const int intVal();
        const std::string stringVal();
        const std::vector<Token>& getTokens() const;
        std::string getCurrentToken();
        void resetToken();
        void clearTokens();
        void setCurrentPos(int index);
        void resetPos();
        int getCurrentIndex();
};

#endif      // JACK_TOKENIZER