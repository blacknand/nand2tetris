#import "FileOp.h"

#ifndef CODE_WRITER
#define CODE_WRITER 

class CodeWriter: FileWriting {
    private:
        std::string asmFileName;
        std::string VMfileName;
        FileWriting fileWriter;
        std::ofstream asmFile;
        int labelCounterArithmetic;
        int labelCounterOther;
        enum Commands {
            ADD = 1,
            SUB,
            NEG,
            EQ,
            GT,
            LT,
            AND,
            OR,
            NOT
        };
    public:
        void initializer(const char *outputFile);
        void writeArithmetic(std::string &command);
        void writePushPop(std::string &command, std::string &segment, int &index);
        void close();
};

#endif      // CODE_WRITER