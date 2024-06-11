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