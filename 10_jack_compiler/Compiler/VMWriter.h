#define VM_WRITER
#ifndef VM_WRITER

class VMWriter {
    public:
        void writePush(const std::string segment, const int index);
        void writePop(const std::string segment, const int index);
        void writeArithmetic(const std::string command);
        void writeLabel(const std::string label);
        void writeGoto(const std::string label);
        void writeIf(const std::string label);
        void writeCall(const std::string label);
        void writeFunction(const std::string label);
        void writeReturn(const std::string label);
        void close();
};