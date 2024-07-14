#ifndef VM_WRITER_H
#define VM_WRITER_H

class VMWriter {
    private:
        std::ofstream vmFile;
    public:
        void initializer(const std::string &outputFile);
        void writePush(const std::string &segment, const int &index, std::string comment = "");
        void writePop(const std::string &segment, const int &index, std::string comment = "");
        void writeArithmetic(const std::string &command, std::string comment = "");
        void writeLabel(const std::string &label, std::string comment = "");
        void writeGoto(const std::string &label, std::string comment = "");
        void writeIf(const std::string &label, std::string comment = "");
        void writeCall(const std::string &label, const int &nArgs, std::string comment = "");
        void writeFunction(const std::string &label, const int &nVars, std::string comment = "");
        void writeReturn();
        void close();
};

#endif  // VM_WRITER_H