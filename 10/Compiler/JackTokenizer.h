#include <iostream>
#include <string>

#ifndef JACK_TOKENIZER
#define JACK_TOKENIZER

class JackTokenizer {
    private:
        static std::vector<std::vector<std::string>> tokenizedVec;
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
        const std::vector<std::vector<std::string>> &getTokenizedVec() {
            return tokenizedVec;
        };

};

#endif      // JACK_TOKENIZER