#include <fstream>
#include <vector>

#ifndef VM_PARSER
#define VM_PARSER

class Parser {
    private:
        std::vector<std::vector<std::string>> fileVect;
        int currentLine = 0;
        std::string currentInstruction;
        enum Commands {
            C_ARITHMETIC = 1,
            C_PUSH,
            C_POP,
            C_LABEL,
            C_GOTO,
            C_IF,
            C_FUNCTION,
            C_RETURN,
            C_CALL
        };
        std::unordered_map<std::string, Commands> commandMap;
    public:
        void initializer(std::ifstream &inputFile);
        bool hasMoreLines();
        void advance();
        const std::string commandType();
        std::string arg1();
        std::string arg2();
        std::vector<std::vector<std::string>> getFileVect() {
            return fileVect;
        }
};

#endif      // VM_PARSER  