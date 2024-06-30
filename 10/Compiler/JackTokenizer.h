#include <iostream>
#include <string>

#ifndef JACK_TOKENIZER
#define JACK_TOKENIZER

class JackTokenizer {
    public:
        struct Token {
            std::string token;
            int lineIndex;
            int tokenIndex;
        };
    private:
        std::vector<Token> tokens;
        // std::vector<std::vector<std::string>> tokenizedVec;
        // int currentLine;
        // int currentToken;
        int currentIndex = 0;
        std::string currentToken;
    public:
        void initializer(std::string inputFile);
        bool hasMoreTokens();
        void advance();
        const std::string &tokenType();
        const std::string &keyWord();
        char symbol();
        std::string identifier();
        int intVal();
        std::string stringVal();
        // const std::vector<std::vector<std::string>> &getTokenizedVec() {
        //     return tokenizedVec;
        // };
        const std::vector<Token>& getTokens() const;
};

#endif      // JACK_TOKENIZER