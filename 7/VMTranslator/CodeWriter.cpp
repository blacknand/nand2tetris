#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"


void CodeWriter::initializer(const char *outputFile) {
    asmFile = fileWriter.writeFile(outputFile);   
}


void CodeWriter::writeArithmetic(std::string &command) {
    labelCounterArithmetic++;
    std::stringstream labelCounterStream;
    std::string labelCounterStr;
    labelCounterStream << labelCounterArithmetic;
    labelCounterStream >> labelCounterStr;

    std::string push = 
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1";

    std::string pop = 
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M";
    
    std::string popR13 = 
        "@R13\n"
        "M=D";

    std::string popR14 = 
        "@R14\n"
        "M=D";

    std::string add = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "M=D+M";

    std::string sub = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M";

    std::string neg = 
        "@R13\n"
        "D=M\n"
        "D=D-D\n"
        "D=D-D";

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
        "D=0";

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
        "D=0";

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
        "D=0";

    std::string bitNot = 
        "@R13\n"
        "D=!M";

    std::string bitAnd = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D&M";

    std::string bitOr =
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D|M";

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

    asmFile << "// pop, popR13" << std::endl;
    asmFile << pop << std::endl;
    asmFile << popR13 << std::endl;

    std::unordered_map<std::string, Commands>::const_iterator commandIter = commandMap.find(command);
    switch (commandIter->second) {
        case 1: 
            asmFile << "// pop, popR14, add" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << add << std::endl;
            break;
        case 2:
            asmFile << "// pop, popR14, sub" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << sub << std::endl;
            break;
        case 3:
            asmFile << "// pop, neg" << std::endl;
            asmFile << neg << std::endl;
            break;
        case 4:
            asmFile << "// pop, popR14, eq" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << eq << std::endl;
            break;
        case 5:
            asmFile << "// pop, popR14, gt" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << gt << std::endl;
            break;
        case 6:
            asmFile << "// pop, popR14, lt" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << lt << std::endl;
            break;
        case 7:
            asmFile << "// pop, popR14, bitAnd" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << bitAnd << std::endl;
            break;
        case 8:
            asmFile << "// pop, popR14, bitOr" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << bitOr << std::endl;
            break;
        case 9:
            asmFile << "// bitNot" << std::endl;
            asmFile << bitNot << std::endl;
            break;
    }

    asmFile << "// push" << std::endl;
    asmFile << push << std::endl;
}


void CodeWriter::writePushPop(std::string &command, std::string &segment, int index) {
    labelCounterOther++;

    std::stringstream labelCounterStream;
    std::string labelCounterStr;
    labelCounterStream << labelCounterOther;
    labelCounterStream >> labelCounterStr;

    std::string strIndex;
    std::stringstream indexStream;
    indexStream << index;
    indexStream >> strIndex;

    // std::unordered_map<std::string, Sections> commandMap = {
    //     {"argument", ARGUMENT},
    //     {"local", LOCAL},
    //     // {"static", STATIC},
    //     // {"constant", CONSTANT},
    //     {"this", THIS},
    //     {"that", THAT}
    //     // {"that", THAT},
    //     // {"pointer", POINTER},
    //     // {"temp", TEMP}
    // };

    // LOCAL, ARGUMENT, THIS, THAT

    std::string push1 = 
        "@" + segment
        "D=M"
        "@" + strIndex;
        "A=D+M"
        "D+M"
        "@SP"
        "A=M"
        "M=D"
        "@SP"
        "M=M+1"

    std::string pop1 = 
        "@" + segment
        "D=M"
        "@" + strIndex;
        "D=D+A"
        "@R15"
        "M=D"
        "@SP"
        "AM=M-1"
        "D=M"
        "@R15"
        "A=M"
        "M=D"

    if (command == "push") {
        asmFile << "// push " + segment " " + strIndex << std::endl;
        asmFile << push1 << std::endl; 
    } else if (command == "pop") {
        asmFile << "// pop " + segment " " + strIndex << std::endl;
        asmFile << pop1 << std::endl; 
    }

    // std::unordered_map<std::string, Sections>::const_iterator commandIter = commandMap.find(command);
    // switch (commandIter->second) {
    //     case 1:
    //         break;
    //     case 2:
    //         break;
    //     case 3:
    //         break;
    //     case 4:
    //         break;
    //     // case 5:
    //     //     break;
    //     // case 6:
    //     //     break;
    //     // case 7:
    //     //     break;
    //     // case 8:
    //     //     break;
    // }

    // std::string pushSegment = 
    //     "@" + 
}


void CodeWriter::close() {
    asmFile.close();
}