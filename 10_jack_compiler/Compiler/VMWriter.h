#include "FileOpp.h"

#ifndef VM_WRITER_H
#define VM_WRITER_H

class VMWriter {
    private:
        WriteToFile fileStream;
        std::ofstream vmFile;
    public:
        VMWriter(const std::string &outputFile);
        void writePush(const std::string &segment, const int &index);
        void writePop(const std::string &segment, const int &index);
        void writeArithmetic(const std::string &command);
        void writeLabel(const std::string &label);
        void writeGoto(const std::string &label);
        void writeIf(const std::string &label);
        void writeCall(const std::string &label, const int &nVars);
        void writeFunction(const std::string &label, const int &nVars);
        void writeReturn();
        void close();
        void write(const std::string &text);
};

#endif  // VM_WRITER_H