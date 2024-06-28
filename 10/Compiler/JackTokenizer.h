#include <iostream>
#include <string>

#ifndef JACK_TOKENIZER
#define JACK_TOKENIZER

class JackTokenizer {
    private:
        std::vector<std::vector<std::string>> lineVect;
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
}

#endif      // JACK_TOKENIZER