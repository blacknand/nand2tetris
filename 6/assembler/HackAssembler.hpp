#include <string>

#ifndef HACK_ASSEMBLER
#define HACK_ASSEMBLER

class Parser {
    public:
        void initializer(std::string inputFile);
        bool hasMoreLines();
        void advance();
        const std::string instructionType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
};

class Code {
    public:
        std::string dest(std::string command);
        std::string comp(std::string command);
        std::string jump(std::string command);
};

class SymbolTable {
    public: 
        void addEntry(std::string symbol, int address);
        bool contains(std::string);
        int getAddress(std::string);
};

#endif