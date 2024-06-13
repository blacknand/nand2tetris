#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"


void CodeWriter::initializer(const char *outputFile) {
    std::ofstream asmFile = fileWriter.writeFile(outputFile);    
    asmFile << "test ahhhh" << std::endl;
}


void CodeWriter::writeArithmetic(std::string command) {
    labelCounter++;
    std::stringstream labelCounterStream;
    std::string labelCounterStr;
    labelCounterStream << labelCounter;
    labelCounterStream >> labelCounterStr;

    std::string push = 
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string pop = 
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M\n";
    
    std::string popR13 = 
        "@R13\n"
        "M=D\n";

    std::string popR14 = 
        "@R14\n"
        "M=D\n";

    std::string add = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "M=D+M\n";

    std::string sub = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M\n";

    std::string neg = 
        "@R13\n"
        "D=M\n"
        "D=D-D\n"
        "D=D-D\n";

    std::string gt = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M\n"
        "@GT" + labelCounterStr + "\n"
        "D;JGT\n"
        "@NO.gt" + labelCounterStr + "\n"
        "0;JMP\n"
        "(GT" + labelCounterStr + ")" + "\n"
        "D=-1\n"
        "(NO.gt" + labelCounterStr + ")" + "\n"
        "D=0\n";

    std::string lt = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M\n"
        "@LT" + labelCounterStr + "\n"
        "D;JLT\n"
        "@NO.lt" + labelCounterStr + "\n"
        "0;JMP\n"
        "(LT" + labelCounterStr + ")" + "\n"
        "D=-1\n"
        "(NO.lt" + labelCounterStr + ")" + "\n"
        "D=0\n";

    std::string eq = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M\n"
        "@EQ" + labelCounterStr + "\n"
        "D;JEQ\n"
        "@NO.eq" + labelCounterStr + "\n"
        "0;JMP\n"
        "(EQ" + labelCounterStr + ")" + "\n"
        "D=-1\n"
        "(NO.eq" + labelCounterStr + ")" + "\n"
        "D=0\n";

    std::string bitNot = 
        "@R13\n"
        "D=!M\n";

    std::string bitAnd = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D&M\n";

    std::string bitOr =
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D|M\n";

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
    };

    asmFile << pop << std::endl;
    asmFile << popR13 << std::endl;

    std::unordered_map<std::string, Commands>::const_iterator commandIter = commandMap.find(command);
    switch (commandIter->second) {
        case 1: 
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << add << std::endl;
            break;
        case 2:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << sub << std::endl;
            break;
        case 3:
            asmFile << neg << std::endl;
            break;
        case 4:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << eq << std::endl;
            break;
        case 5:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << gt << std::endl;
            break;
        case 6:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << lt << std::endl;
            break;
        case 7:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << bitAnd << std::endl;
            break;
        case 8:
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << bitOr << std::endl;
            break;
        case 9:
            asmFile << bitNot << std::endl;
            break;
    }

    asmFile << push << std::endl;
}


void CodeWriter::writePushPop(std::string command, std::string segment, int index) {

}


void CodeWriter::close() {
    asmFile.close();
}