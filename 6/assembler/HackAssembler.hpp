#include <string>
#include <vector>

#ifndef HACK_ASSEMBLER
#define HACK_ASSEMBLER

class Parser {
    private:
        int currentLine = 0;
        std::string currentInstruction;
        std::vector<std::vector<std::string>> lineVect;
        std::vector<std::vector<std::string>> strippedVect;
    public:
        void initializer(std::string inputFile);
        void close(std::string inputFile);
        bool hasMoreLines();
        void advance();
        const std::string instructionType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
        // Getter
        void setCurrentLine(int num) {
            currentLine = num;
        }
        void setVect(std::vector<std::vector<std::string>> vect) {
            lineVect = vect;
        }
        void setStrippedVect(std::vector<std::vector<std::string>> lineVect) {
            strippedVect = lineVect;
        }
        void setCurrentInstruct(std::string instruct) {
            currentInstruction = instruct;
        }
        // Setter
        int getCurrentLine() {
            return currentLine;
        }
        std::vector<std::vector<std::string>> getVect() {
            return lineVect;
        }
        std::vector<std::vector<std::string>> getStrippedVect() {
            return strippedVect;
        }
        std::string getCurrentInstruct() {
            return currentInstruction;
        }
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