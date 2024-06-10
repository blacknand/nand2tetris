#include <fstream>
#include <vector>

#ifndef VM_PARSER
#define VM_PARSER

class Parser {
    private:
        std::vector<std::vector<std::string>> fileVect;
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


#ifndef CODE_WRITER
#define CODE_WRITER 

class CodeWriter {
    public:
        void initializer(const std::ofstream &outputFile);
        void writeArithmetic(std::string command);
        void writePushPop(std::string command, std::string segment, int index);
        void close(const std::ofstream &outputFile);
};

#endif      // CODE_WRITER