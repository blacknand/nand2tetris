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
        void initializer(const char *outputFile, const std::string &VMFileName);
        void writeArithmetic(std::string &command);
        void writePushPop(std::string &command, std::string &segment, int &index);
        void close();
        void CodeWriter::setFileName(const std::string &fileName);
        void CodeWriter::writeLabel(const std::string &label, const std::string &funcName);
        void CodeWriter::writeGoto(const std::string &label, const std::string &funcName);
        void CodeWriter::writeIf(const std::string &label, const std::string &funcName);
        void CodeWriter::writeFunction(const std::string &functionName, const int &nVars);
        void CodeWriter::writeCall(const std::string &functionName, const int &nVars);
        void CodeWriter::return();
        void setFileName(const std::string &fileName) {
            
        }
};

#endif      // CODE_WRITER