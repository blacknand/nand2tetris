#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "FileOpp.h"
#include "VMWriter.h"


VMWriter::VMWriter(const std::string &outputFile) :
    vmFile(outputFile.c_str()) {};


void VMWriter::writePush(const std::string &segment, const int &index) {
    vmFile << "push " << segment << " " << index << std::endl;
}


void VMWriter::writePop(const std::string &segment, const int &index) {
    vmFile << "pop " << segment << " " << index << std::endl;
}


void VMWriter::writeArithmetic(const std::string &command) {
    vmFile << command << std::endl;
}


void VMWriter::writeLabel(const std::string &label) {
    vmFile << "label " << label << std::endl; 
}


void VMWriter::writeGoto(const std::string &label) {
    vmFile << "goto " << label << std::endl;
}


void VMWriter::writeIf(const std::string &label) {
    vmFile << "if-goto " << label << std::endl;
}


void VMWriter::writeCall(const std::string &label, const int &nArgs) {
    vmFile << "call " << label << " " << nArgs << std::endl;
}


void VMWriter::writeFunction(const std::string &label, const int &nVars) {
    vmFile << "function " << label << " " << nVars << std::endl;
}


void VMWriter::writeReturn() {
    vmFile << "return" << std::endl;
}


void VMWriter::close() {
    if (vmFile.is_open())
        vmFile.close();
}


void VMWriter::write(const std::string &text) {
    vmFile << text << std::endl;
}
