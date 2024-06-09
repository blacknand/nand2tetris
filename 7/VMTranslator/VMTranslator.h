#include <fstream>

#ifndef VM_PARSER
#define VM_PARSER

class Parser {
    public:
        void initializer(std::ifstream inputFile);
        bool hasMoreLines();
        void advance();
        const std::string commandType();
        std::string arg1();
        std::string arg2();
};

#endif      // VM_PARSER    


#ifndef CODE_WRITER
#define CODE_WRITER 

class CodeWriter {
    public:
        void initializer(std::ofstream outputFile);
        void writeArithmetic(std::string command);
        void writePushPop(std::string command, std::string segment, int index);
        void close(std::ofstream outputFile);
};

#endif      // CODE_WRITER