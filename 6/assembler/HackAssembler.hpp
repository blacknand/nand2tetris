#include <string>
#include <vector>

#ifndef HACK_ASSEMBLER
#define HACK_ASSEMBLER

class Parser {
    private:
        int lineCount;
        int currentLine;
        std::vector<std::vector<std::string>> lineVect;
        std::vector<std::vector<std::string>> strippedVect;
    public:
        void initializer(std::string inputFile);
        void close(std::string inputFile);
        bool hasMoreLines(int lineCount, int currentLine);
        void advance(int currentLine);
        const std::string instructionType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
        // Getter
        void setLineCount(int num) {
            lineCount = num;
        }
        void setCurrentLine(int num) {
            currentLine = num;
        }
        void setVect(std::vector<std::vector<std::string>> vect) {
            lineVect = vect;
        }
        void setStrippedVect(std::vector<std::vector<std::string>> lineVect) {
            strippedVect = lineVect;
        }
        // Setter
        int getLineCount() {
            return lineCount;
        }
        int getCurrentLine() {
            return currentLine;
        }
        std::vector<std::vector<std::string>> getVect() {
            return lineVect;
        }
        std::vector<std::vector<std::string>> getStrippedVect() {
            return strippedVect;
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