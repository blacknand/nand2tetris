#include <string>
#include <vector>

#ifndef ASSEMBLER_PARSER
#define ASSEMBLER_PARSER

class Parser {
    private:
        int currentLine = 0;
        std::string currentInstruction;
        std::vector<std::vector<std::string>> lineVect;
        bool secondPass;
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
        void setCurrentInstruct(std::string instruct) {
            currentInstruction = instruct;
        }
        void setSecondPass(bool pass) {
            secondPass = pass;
        }
        // Setter
        int getCurrentLine() {
            return currentLine;
        }
        std::vector<std::vector<std::string>> getVect() {
            return lineVect;
        }
        std::string getCurrentInstruct() {
            return currentInstruction;
        }
        bool getSecondPass() {
            return secondPass;
        }
};

#endif  // Parser


#ifndef ASSEMBLER_CODE
#define ASSEMBLER_CODE

class Code {
    public:
        std::string dest(const std::string &destCode);
        std::string comp(const std::string &compCode);
        std::string jump(const std::string &jumpCode);
};

#endif  // Code


#ifndef ASSEMBLER_SYMBOL_TABLE
#define ASSEMBLER_SYMBOL_TABLE

class SymbolTable {
    private:
        std::map<std::string, int> symbolTable;
    public: 
        void initializeTable();
        void addEntry(const std::string &symbol, const int &address);
        bool contains(const std::string &symbol);
        int getAddress(const std::string &symbol);
        void setSymbolTable(std::map<std::string, int> map) {
            symbolTable = map;
        }
        std::map<std::string, int> getSymbolTable() {
            return symbolTable;
        }
};

#endif  // SymbolTable