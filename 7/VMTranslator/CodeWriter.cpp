#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"


void CodeWriter::initializer(const char *outputFile) {
    std::ofstream asmFile = fileWriter.writeFile(outputFile);    
}


void CodeWriter::writeArithmetic(std::string command) {
    const char *push = 
        "@SP"
        "A=M"
        "M=D"
        "@SP"
        "M=M+1"

    const char *pop = 
        "@SP"
        "M-M-1"
        "A=M"
        "D=M"
    
    const char *popR13 = 
        "@R13"
        "M=D"

    const char *popR14 = 
        "@R14"
        "M=D"

    const char *add = 
        "@R13"
        "D=M"
        "@R14"
        "M=D+M"

    const char *sub = 
        "@R13"
        "D=M"
        "@R14"
        "D=D-M"

    const char *neg = 
        "@R13"
        "D=M"
        "D=D-D"
        "D=D-D"

    const char *gt = 
        "@R13"
        "D=M"
        "@R14"
        "D=D-M"
        "@GT"
        "D;JGT"
        "@NO"
        "0;JMP"
        "(GT)"
        "D=-1"
        "(NO)"
        "D=0"

    const char *lt = 
        "@R13"
        "D=M"
        "@R14"
        "D=D-M"
        "@LT"
        "D;JLT"
        "@NO"
        "0;JMP"
        "(LT)"
        "D=-1"
        "(NO)"
        "D=0"

    const char *eq = 
        "@R13"
        "D=M"
        "@R14"
        "D=D-M"
        "@EQ"
        "D;JEQ"
        "@NO"
        "0;JMP"
        "(EQ)"
        "D=-1"
        "(NO)"
        "D=0"

    const char *bitNot = 
        "@R13"
        "D=!M"

    const char *bitAnd = 
        "@R13"
        "D=M"
        "@R14"
        "D=D&M"

    const char *bitOr =
        "@R13"
        "D=M"
        "@R14"
        "D=D|M"

    std::unordered_map<std::string, Commands> commandMap = {
        {"add", ADD},
        {"sub", SUB},
        {"neg", NEG},
        {"eq", EQ},
        {"gt", GT},
        {"lt", LT},
        {"and", AND},
        {"or", OR},
        {"not", NOT}
    }

    // pop first 2 off of stack
    // choose command
    // push result back onto stack and then return

    asmFile << pop << std::endl;
    asmFile << pop << std::endl;
    std::unordered_map<std::string, Commands>::const_iterator commandIter = commandMap.find(command);
    switch (commandIter->second) {
        case 1:

            break;
    }

    asmFile << pop << std::endl;


}


void CodeWriter::writePushPop(std::string command, std::string segment, int index) {

}


void CodeWriter::close() {
    asmFile.close();
}