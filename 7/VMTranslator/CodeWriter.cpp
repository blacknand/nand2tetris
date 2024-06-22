#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"


void CodeWriter::writeDebugMarker() {
    std::string debugMarker =
        "@7777\n"
        "M=0\n"
        "M=1\n";
    asmFile << debugMarker << std::endl;
}


void CodeWriter::initializer(const char *outputFile) {
    asmFile = fileWriter.writeFile(outputFile);   
    // writeDebugMarker(); 
    std::string push = 
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string returnLabel = "Sys.init$ret.0";
    std::string bootstrapASM =
        "// -------------------- bootstrapASM --------------------\n"
        "@261\n"
        "D=A\n"
        "@SP\n"
        "M=D\n"
        "@Sys.init\n"
        "// -------------------- bootstrapASM --------------------\n"
        "0;JMP\n"
        "(" + returnLabel + ")\n";
    
    writeDebugMarker();
    asmFile << bootstrapASM << std::endl;
}


void CodeWriter::writeArithmetic(std::string &command) {
    // writeDebugMarker();
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
        "D=D+M\n";

    std::string sub = 
        "@R13\n"
        "D=M\n"
        "@R14\n"
        "D=D-M\n";

    std::string neg = 
        "@R13\n"
        "D=-M\n";

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
        "@GT.skip" + labelCounterStr + "\n"
        "0;JMP\n"
        "(NO.gt" + labelCounterStr + ")" + "\n"
        "D=0\n"
        "(GT.skip" + labelCounterStr + ")" + "\n";

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
        "@LT.skip" + labelCounterStr + "\n"
        "0;JMP\n"
        "(NO.lt" + labelCounterStr + ")" + "\n"
        "D=0\n"
        "(LT.skip" + labelCounterStr + ")" + "\n";

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
        "@EQ.skip" + labelCounterStr + "\n"
        "0;JMP\n"
        "(NO.eq" + labelCounterStr + ")" + "\n"
        "D=0\n"
        "(EQ.skip" + labelCounterStr + ")" + "\n";

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

    std::unordered_map<std::string, Commands>::const_iterator commandIter = commandMap.find(command);
    switch (commandIter->second) {
        case 1: 
            asmFile << "// -------------- pop R13 and R14, add ------------------" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR14 << "      // save to R14" << std::endl;
            asmFile << add << "     // add" << std::endl;
            asmFile << "// -------------- pop R13 and R14, add ------------------" << std::endl;
            break;
        case 2:
            asmFile << "// ---------------- pop R14 and R13, sub -----------------" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR14 << "      // save to R14" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << sub << "     // sub" << std::endl;
            asmFile << "// ---------------- pop R14 and R13, sub -----------------" << std::endl;
            break;
        case 3:
            asmFile << "// ------------------- popR13, neg ------------------------" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << neg << std::endl;
            asmFile << "// ------------------- popR13, neg ------------------------" << std::endl;
            break;
        case 4:
            asmFile << "// -------------------- popR14 and popR13, eq ------------------------" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR14 << "      // save to R14" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << eq << std::endl;
            asmFile << "// -------------------- popR14 and popR13, eq ------------------------" << std::endl;
            break;
        case 5:
            asmFile << "// ---------------------- popR14 and popR13, gt --------------------------" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << gt << std::endl;
            asmFile << "// ---------------------- popR14 and popR13, gt --------------------------" << std::endl;
            break;
        case 6:
            asmFile << "// ------------------------- pop14 and popR13, lt --------------------------" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << lt << std::endl;
            asmFile << "// ------------------------- pop14 and popR13, lt --------------------------" << std::endl;
            break;
        case 7:
            asmFile << "// ------------------------------- popR14 and popR13, bitAnd ------------------------" << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << bitAnd << std::endl;
            asmFile << "// ------------------------------- popR14 and popR13, bitAnd ------------------------" << std::endl;
            break;
        case 8:
            asmFile << "// -------------------------------  popR14 and popR13, bitOr ------------------------------- " << std::endl;
            asmFile << pop << std::endl;
            asmFile << popR14 << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << bitOr << std::endl;
            asmFile << "// -------------------------------  popR14 and popR13, bitOr ------------------------------- " << std::endl;
            break;
        case 9:
            asmFile << "// ------------------------------- pop R13, bitNot -------------------------------" << std::endl;
            asmFile << pop << "     // pop" << std::endl;
            asmFile << popR13 << "      // save to R13" << std::endl;
            asmFile << bitNot << std::endl;
            asmFile << "// ------------------------------- pop R13, bitNot -------------------------------" << std::endl;
            break;
    }

    asmFile << "// push" << std::endl;
    asmFile << push << std::endl;
}


void CodeWriter::writePushPop(std::string &command, std::string &segment, int &index) {
    labelCounterOther++;
    // writeDebugMarker();
    std::stringstream labelCounterStream;
    std::string labelCounterStr;
    labelCounterStream << labelCounterOther;
    labelCounterStream >> labelCounterStr;

    // if (segment == "temp")
    //     index = index + 5;

    std::string strIndex;
    std::stringstream indexStream;
    indexStream << index;
    indexStream >> strIndex;

    std::string ogSegment = segment;

    if (segment == "local")
        segment = "LCL";
    else if (segment == "argument")
        segment = "ARG";
    else if (segment == "this")
        segment = "THIS";
    else if (segment == "that")
        segment = "THAT";
    else if (segment == "pointer" && index == 0)
        segment = "THIS";
    else if (segment == "pointer" && index == 1)
        segment = "THAT";

    std::string push1 = 
        "@" + segment + "\n"
        "D=M\n"
        "@" + strIndex + "\n"
        "A=D+A\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string pop1 = 
        "@" + segment + "\n"
        "D=M\n"
        "@" + strIndex + "\n"
        "D=D+A\n"
        "@R15\n"
        "M=D\n"
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@R15\n"
        "A=M\n"
        "M=D\n";

    std::string pushPointer = 
        "@" + segment + "\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string popPointer = 
        "@" + segment + "\n"
        "D=A\n"             
        "@R15\n"
        "M=D\n"
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@R15\n"
        "A=M\n"
        "M=D\n";

    std::string pushTemp = 
        "@" + std::to_string(5 + index) + "\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string popTemp = 
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M\n"
        "@" + std::to_string(5 + index) + "\n"
        "M=D\n";

    std::string pushConst = 
        "@" + strIndex + "\n"
        "D=A\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string pushStatic = 
        "@" + currentFileName + "." + strIndex + "\n"
        "D=M\n"
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";

    std::string popStatic = 
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@" + currentFileName + "." + strIndex + "\n"
        "M=D\n";

    std::string segmentsArr[5] = {"LCL", "ARG", "THIS", "THAT"};
    std::string *foundSegment = std::find(std::begin(segmentsArr), std::end(segmentsArr), segment);

    if (command == "C_PUSH" && ogSegment == "pointer") {
        asmFile << "// push ------------------------- " + ogSegment + " " + strIndex << std::endl;
        asmFile << pushPointer << std::endl;
        asmFile << "// push ------------------------- " + ogSegment + " " + strIndex << std::endl;
    } else if (command == "C_POP" && ogSegment == "pointer") {
        asmFile << "// pop ------------------------- " + ogSegment + " " + strIndex << std::endl;
        asmFile << popPointer << std::endl;
        asmFile << "// pop ------------------------- " + ogSegment + " " + strIndex << std::endl;
    } else if (command == "C_PUSH" && foundSegment != std::end(segmentsArr)) {
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << push1 << std::endl; 
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_POP" && foundSegment != std::end(segmentsArr)) {
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << pop1 << std::endl; 
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_POP" && segment == "temp") {
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << popTemp << std::endl; 
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_PUSH" && segment == "temp") {
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << pushTemp << std::endl; 
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_PUSH" && segment == "constant") {
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << pushConst << std::endl;
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_PUSH" && segment == "static") {
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << pushStatic << std::endl;
        asmFile << "// push -------------------------" + segment + " " + strIndex << std::endl;
    } else if (command == "C_POP" && segment == "static") {
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
        asmFile << popStatic << std::endl;
        asmFile << "// pop -------------------------" + segment + " " + strIndex << std::endl;
    }
}


void CodeWriter::close() {
    // writeDebugMarker();
    std::string endLoop = 
        "@END\n"
        "(END)\n"
        "@END\n"
        "0;JMP\n";
    asmFile << endLoop << std::endl;
    asmFile.close();
}


void CodeWriter::setFileName(const std::string &fileName) {
    currentFileName = fileName;
}


void CodeWriter::writeLabel(const std::string &label) {
    // writeDebugMarker();
    std::string funcName = currentFuncName.empty() ? "NULL" : currentFuncName;
    std::string writeLabelASM =
        // "(" + currentFileName + "." + funcName + "$" + label + ")\n";
        "(" + funcName + "$" + label + ")\n";
    asmFile << writeLabelASM << std::endl;
}


void CodeWriter::writeGoto(const std::string &label) {
    // writeDebugMarker();
    std::string funcName = currentFuncName.empty() ? "NULL" : currentFuncName;
    std::string writeGotoASM =
        " // ------------------------- writeGoto ---------------------\n"
        // "@" + currentFileName + "." + funcName + "$" + label + "\n"
        "@" + funcName + "$" + label + "\n"
        " // ------------------------- writeGoto ---------------------\n"
        "0;JMP\n";
    asmFile << writeGotoASM << std::endl;
}


void CodeWriter::writeIf(const std::string &label) {
    // writeDebugMarker();
    std::string funcName = currentFuncName.empty() ? "NULL" : currentFuncName;
    std::string writeIfASM = 
        " // ------------------------- writeIf ---------------------\n"
        "@SP\n"
        "M=M-1\n"
        "A=M\n"
        "D=M\n"
        // "@" + currentFileName + "." + funcName + "$" + label + "\n"
        "@" + funcName + "$" + label + "\n"
        " // ------------------------- writeIf ---------------------\n"
        "D;JNE\n";
    asmFile << writeIfASM << std::endl;
}


void CodeWriter::writeFunction(const std::string &functionName, const int &nVars) {
    // writeDebugMarker();
    currentFuncName = functionName;
    std::string writeFunctionASM = 
        " // ------------------------- writeFunction" + functionName + std::to_string(nVars) + " ---------------------\n"
        // "(" + currentFileName + "." + functionName + ")\n";
        "(" + functionName + ")\n";
    for (int i = 0; i < nVars; i++) {
        writeFunctionASM += 
            "@SP\n"
            "A=M\n"
            "M=0\n" 
            "@SP\n"
            "M=M+1\n";
    }
    writeFunctionASM += 
        " // ------------------------- writeFunction ---------------------\n";

    asmFile << writeFunctionASM << std::endl;
}


void CodeWriter::writeCall(const std::string &functionName, const int &nArgs) {
    // writeDebugMarker();
    static int runningInt = 0;
    // std::string returnLabel = currentFileName + "." + functionName + "$ret." + std::to_string(runningInt);
    std::string returnLabel = functionName + "$ret." + std::to_string(runningInt);
    std::string push = 
        "@SP\n"
        "A=M\n"
        "M=D\n"
        "@SP\n"
        "M=M+1\n";
    std::string writeCallASM =  
        "// -------------------- writeCall" + functionName + std::to_string(nArgs) + " -------------------\n"
        "@" + returnLabel + "\n"
        "D=A\n" + push + 
        "@LCL\n"
        "D=M\n" + push +
        "@ARG\n"
        "D=M\n" + push +
        "@THIS\n"
        "D=M\n" + push +
        "@THAT\n"
        "D=M\n" + push +
        // ARG = SP - 5 - nArgs
        "@SP\n"
        "D=M\n"
        "@" + std::to_string(nArgs + 5) + "\n"
        "D=D-A\n"
        "@ARG\n"
        "M=D\n"
        // LCL = SP
        "@SP\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n"
        // goto f
        "@" + functionName + "\n"
        "// -------------------- writeCall" + functionName + std::to_string(nArgs) + " -------------------\n"
        "0;JMP\n"
        "(" + returnLabel + ")\n";
    asmFile << writeCallASM << std::endl;
    runningInt++;
}


void CodeWriter::writeReturn() {
    // R15 == frame
    // R14 == retAddr
    std::string writeReturnASM = 
        "// -------------------- writeReturn -------------------\n"
        // frame = LCL
        "@LCL\n"
        "D=M\n"
        "@R15\n"
        "M=D\n"
        // retAddr = *(frame - 5)
        "@5\n"
        "A=D-A\n"
        "D=M\n"
        "@R14\n"
        "M=D\n"
        // *ARG = pop()
        "@SP\n"
        "AM=M-1\n"  // Decrement SP and access the top value
        "D=M\n"
        "@ARG\n"
        "A=M\n"
        "M=D\n"
        // SP = ARG + 1
        "@ARG\n"
        "D=M+1\n"
        "@SP\n"
        "M=D\n"
        // THAT = *(frame - 1)
        "@R15\n"
        "D=M\n"
        "A=D-1\n"
        "D=M\n"
        "@THAT\n"
        "M=D\n"
        // THIS *(frame - 2)
        "@2\n"
        "D=A\n"
        "@R15\n"
        "A=M-D\n"
        "D=M\n"
        "@THIS\n"
        "M=D\n"
        // ARG = *(frame - 3)
        "@3\n"
        "D=A\n"
        "@R15\n"
        "A=M-D\n"
        "D=M\n"
        "@ARG\n"
        "M=D\n"
        // LCL = *(frame - 4)
        "@4\n"
        "D=A\n"
        "@R15\n"
        "A=M-D\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n"
        // goto retAddr
        "@R14\n"
        "A=M\n"
        "0;JMP\n"
        "// -------------------- writeReturn -------------------\n";

    asmFile << writeReturnASM << std::endl;
}
