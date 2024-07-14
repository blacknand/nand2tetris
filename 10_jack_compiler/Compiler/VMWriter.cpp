#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "FileOpp.h"
#include "VMWriter.h"


void VMWriter::initializer(const std::string &outputFile) {
    if (vmFile.is_open())
        vmFile.close();
    vmFile.open(outputFile.c_str());
}

void VMWriter::writePush(const std::string &segment, const int &index, std::string comment) {
    vmFile << "push " << segment << " " << index << std::endl;
}


void VMWriter::writePop(const std::string &segment, const int &index, std::string comment) {
    vmFile << "pop " << segment << " " << index << std::endl;
}


void VMWriter::writeArithmetic(const std::string &command, std::string comment) {
    vmFile << command << std::endl;
}


void VMWriter::writeLabel(const std::string &label, std::string comment) {
    vmFile << "label " << label << std::endl; 
}


void VMWriter::writeGoto(const std::string &label, std::string comment) {
    vmFile << "goto " << label << std::endl;
}


void VMWriter::writeIf(const std::string &label, std::string comment) {
    vmFile << "if-goto " << label << std::endl;
}


void VMWriter::writeCall(const std::string &label, const int &nArgs, std::string comment) {
    vmFile << "call " << label << " " << nArgs << std::endl;
}


void VMWriter::writeFunction(const std::string &label, const int &nVars, std::string comment) {
    vmFile << "function " << label << " " << nVars << std::endl;
}


void VMWriter::writeReturn() {
    vmFile << "return" << std::endl;
}


void VMWriter::close() {
    if (vmFile.is_open())
        vmFile.close();
}
