#include <iostream>
#include <string>

#ifndef INITIALIZER
#define INITIALIZER

class Initializer {
    public:
        void initializer(const char *inputFile);
        bool hasMoreTokens();
        void advance();
        const std::string &tokenType() const;
        const std::string &keyWord() const;
        char symbol();
        std::string identifier();
        int intVal();
        std::string stringVal();
}

#endif      // INITIALIZER