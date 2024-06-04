/*
    Implementation of an assembler for the Hack computer. Converts Hack
    assembly language code into binary code and generates a .hack file.

    The assembler does not perform error checking of any kind and it is 
    assumed that the assembley code is error free.
*/


#include <cctype>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map> 
#include <vector>
#include "HackAssembler.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./HackAssembler prog.asm" << std::endl;
        return 1;
    }

    Parser parser;
    Code code;
    parser.initializer(argv[1]);
    std::vector<std::vector<std::string>> lineVect = parser.getVect();
    // std::string currentInstruction = parser.getCurrentInstruct();

    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            if (parser.hasMoreLines()) {
                parser.advance();
                std::string instruction = parser.instructionType();
                std::cout << instruction << std::endl;
                if (instruction == "C_INSTRUCTION") {
                    std::string instructionDest = parser.dest();
                    // std::cout << "instructionDest" << instructionDest << std::endl;
                    std::string instructionComp = parser.comp();
                    std::cout << "comp: " << instructionComp << std::endl;
                    std::string instructionJump = parser.jump();
                    // std::cout << instructionJump << std::endl;

                    std::string destBinary = code.dest(instructionDest);
                    std::string compBinary = code.comp(instructionComp);
                    std::string jumpBinary = code.jump(instructionJump);
                    std::string instructionBinary = destBinary + compBinary + jumpBinary;
                } else if (instruction == "A_INSTRUCTION") {
                    std::cout << "is a A instruction" << std::endl;
                }
            }
        }
    }
    // for each line in asm file
        // for c-instruction, user parser and code to translate
            // concatenate binary string
            // write to .hack file
        // for a-instruction, user other thing and write to .hack file


    return 0;
}


void Parser::initializer(std::string inputFile) {
    // Open .asm file and read into a 2d vector to be operated on
    std::string line;
    std::ifstream asmFile(inputFile);
    if (asmFile.is_open()) {
        while (getline(asmFile, line)) {
            std::vector<std::string> singleLine;
            singleLine.push_back(line);
            lineVect.push_back(singleLine);
        }
        asmFile.close();
    } else
        std::cout << "Failed to open " << inputFile << std::endl;
}


bool Parser::hasMoreLines() {
    // Returns if there are any more valid lines (i.e. not a comment line)
    int iter = (currentLine > 0) ? ++currentLine : 0;

    for (int i = iter; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::size_t foundWhiteSpace = lineVect[i][j].find_first_not_of(' ');
            if (foundWhiteSpace != std::string::npos) {
                if (lineVect[i][j].substr(foundWhiteSpace, 2) != "//")
                    return true;
                else
                    continue;
            }
        }
    }

    return false;
}


void Parser::advance() {
    // Reads the next instruction from input and makes current instruction
    int iter = (currentLine > 0) ? ++currentLine : 0;

    for (int i = iter; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            std::size_t foundWhiteSpace = lineVect[i][j].find_first_not_of(' ');
            if (foundWhiteSpace != std::string::npos) {
                if (lineVect[i][j].substr(foundWhiteSpace, 2) != "//") {
                    currentLine = i;
                    currentInstruction = lineVect[i][j];
                    return;
                } else    
                    continue;
            }
        }
    }

}


const std::string Parser::instructionType() {
    // Returns the current type of the instruction
    std::size_t pos = currentInstruction.find_first_not_of(' ');
    std::string instruction = currentInstruction.substr(pos);
    std::string::size_type ch = currentInstruction.find_last_not_of(' ');

    /*
        A_INSTRUCTION for @xxx, where xxx is a symbol for 
        either a decimal number or a symbol.

        C_INSTRUCTION for dest=comp;jump

        L_INSTRUCTION for (xxx), where xxx is a symbol.
    */
    if (instruction[0] == '@') {
        return "A_INSTRUCTION";
    } else if (instruction.find('=') != std::string::npos || instruction.find(';') != std::string::npos) {
        return "C_INSTRUCTION";
    } else if (instruction[0] == '(' && instruction[ch] == ')') {
        return "L_INSTRUCTION";
    }

    return "\nParser::instructionType() error: have encountered erreneous instruction";
}


std::string Parser::symbol() {
    // Strips the decimal/symbol from the A/L-instruction
    std::size_t pos = currentInstruction.find_first_not_of(' ');
    std::string instruction = currentInstruction.substr(pos);
    std::string::size_type ch = currentInstruction.find_last_not_of(' ');

    if (instruction[0] == '@') {
        return instruction.substr(1, ch);
    } else if (instruction[0] == '(' && instruction[ch] == ')') {
        return instruction.substr(1, --ch);
    }

    return "\nParser::symbol() error: have encountered erreneous instruction";
}


std::string Parser::dest() {
    // Returns the dest part of a C-instruction
    std::size_t destStr = currentInstruction.find('=');

    if (destStr != std::string::npos) {
        std::size_t pos = currentInstruction.find_first_not_of(' ');
        std::string instruction = currentInstruction.substr(pos);
        return instruction.substr(pos, destStr);
    } else
        return "null";
}


std::string Parser::comp() {
    // Returns the comp part of a C-instruction
    std::size_t pos = currentInstruction.find_first_not_of(' ');
    std::string instruction = currentInstruction.substr(pos);
    std::size_t destStr = currentInstruction.find('=');
    std::size_t jumpStr = currentInstruction.find(';');
    std::cout << "pos: " << pos << "\ninstruction: " << instruction << "\ndestStr: " << destStr << "\njumpStr: " << jumpStr << std::endl;

    if (destStr != std::string::npos && jumpStr == std::string::npos) {
        return instruction.substr(++destStr);
    }
    else if (jumpStr != std::string::npos && destStr == std::string::npos) {
        return instruction.substr(0, jumpStr);
    }
    else if (destStr != std::string::npos && jumpStr != std::string::npos) {
        std::size_t compStr = jumpStr - ++destStr;
        return instruction.substr(destStr, compStr);
    }

    return "\nParser::comp() error: have encountered erreneous instruction";
}


std::string Parser::jump() {
    // Returns the jump part of a C-instruction
    std::size_t jumpStr = currentInstruction.find(';');
    std::string::size_type ch = currentInstruction.find_last_not_of(' ');

    if (jumpStr != std::string::npos) 
        return currentInstruction.substr(++jumpStr, ch);

    return "null";
}


std::string Code::dest(const std::string &destCode) {
    std::unordered_map<std::string, std::string> destCodeMap = {
        {"M", "001"},
        {"D", "010"},
        {"DM", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"ADM", "111"},
        {"null", "000"}
    };

    std::unordered_map<std::string, std::string>::const_iterator code = destCodeMap.find(destCode);
    if (code != destCodeMap.end())
        return code->second;
    else
        return "\nCode::dest(std::string destCode) error: have encountered errenuous instruction";
}


std::string Code::comp(const std::string &compCode) {
    std::unordered_map<std::string, std::string> compCodeMap = {
        {"0", "101010"},
        {"1", "111111"},
        {"-1", "111010"},
        {"D", "001100"},
        {"A", "110000"},
        {"M", "110000"},
        {"!D", "001101"},
        {"!A", "110001"},
        {"!M", "110001"},
        {"-D", "001111"},
        {"-A", "110011"},
        {"-M", "110011"},
        {"D+1", "011111"},
        {"A+1", "110111"},
        {"M+1", "110111"},
        {"D-1", "001110"},
        {"A-1", "110010"},
        {"M-1", "110010"},
        {"D+A", "000010"},
        {"D+M", "000010"},
        {"D-A", "010011"},
        {"D-M", "010011"},
        {"A-D", "000111"},
        {"M-D", "000111"},
        {"D&A", "000000"},
        {"D&M", "000000"},
        {"D|A", "010101"},
        {"D|M", "010101"}
    };

    std::unordered_map<std::string, std::string>::const_iterator code = compCodeMap.find(compCode);
    if (code != compCodeMap.end())
        return code->second;
    else
        return "\nCode::comp(std::string compCode) error: have encountered errenuous instruction";
}


std::string Code::jump(const std::string &jumpCode) {
    std::unordered_map<std::string, std::string> jumpCodeMap = {
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"},
        {"null", "000"}
    };

    std::unordered_map<std::string, std::string>::const_iterator code = jumpCodeMap.find(jumpCode);
    if (code != jumpCodeMap.end())
        return code->second;
    else
        return "\nCode::jump(std::string jumpCode) error: have encountered errenuous instruction";
}