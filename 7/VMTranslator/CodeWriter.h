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
        std::string currentFuncName;
        std::string currentFileName;
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
        void setFileName(const std::string &fileName);
        void writeLabel(const std::string &label);
        void writeGoto(const std::string &label);
        void writeIf(const std::string &label);
        void writeFunction(const std::string &functionName, const int &nVars);
        void writeCall(const std::string &functionName, const int &nVars);
        void writeReturn();
        void setterFileName(const std::string &fileName) {
            currentFileName = fileName;
        }
};

#endif      // CODE_WRITER