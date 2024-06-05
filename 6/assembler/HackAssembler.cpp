/*
    Implementation of an assembler for the Hack computer. Converts Hack
    assembly language code into binary code and generates a .hack file.

    The assembler does not perform error checking of any kind and it is 
    assumed that the assembley code is error free.
*/


#include <algorithm>
#include <bitset>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
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

    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            if (parser.hasMoreLines()) {
                parser.advance();

                std::string instruction = parser.instructionType();
                std::string hackFileName = argv[0];
                int hackFileNamePos = hackFileName.find_first_not_of("./");
                hackFileName = hackFileName.substr(hackFileNamePos) + ".hack";
                std::ofstream hackFile;
                hackFile.open(hackFileName, std::ios::app);

                if (instruction == "C_INSTRUCTION") {
                    std::string instructionDest = parser.dest();
                    std::string instructionComp = parser.comp();
                    std::string instructionJump = parser.jump();
                    std::cout << "---------------------------------------------------------------" << std::endl;
                    // std::cout << "dest: " << instructionDest << " comp: " << instructionComp << " jump: " << instructionJump << std::endl;
                    std::string destBinary = code.dest(instructionDest);
                    std::string compBinary = code.comp(instructionComp);
                    std::string jumpBinary = code.jump(instructionJump);
                    std::string cInstructionBinary = "111" + compBinary + destBinary + jumpBinary;
                    hackFile << cInstructionBinary << std::endl;
                } else if (instruction == "A_INSTRUCTION") {
                    std::string aInstruction = parser.symbol();
                    int aDigit = std::stoi(aInstruction);
                    std::string aInstructionBinary = "0" + std::bitset<15>(aDigit).to_string();
                    hackFile << aInstructionBinary << std::endl;
                }
            }
        }
    }
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
    int iter = (currentLine > 0) ? (currentLine + 1) : 0;

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
    int iter = (currentLine > 0) ? (currentLine + 1) : 0;

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

    return "\nParser::instructionType() error: instruction " + currentInstruction;
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

    return "\nParser::symbol() error: instruction " + currentInstruction;
}


// PARSER DEST COMP AND JUMP R NOT OUTPUTTING CORRECT VALUES

// NEED TO IGNORE ALL WHITESPACE
// NEED TO IGNORE ALL \R
// NEED TO IGNORE ALL \N
// NEED TO IGNORE ALL TABS

std::string Parser::dest() {
    // Returns the dest part of a C-instruction
    boost::algorithm::trim(currentInstruction);
    // std::cout << "Parser::dest(): " << instruction.substr(pos, destStr) << std::endl;
    std::size_t destStr = currentInstruction.find('=');

    if (destStr != std::string::npos) {
        // std::size_t pos = currentInstruction.find_first_not_of(' ');
        // std::size_t testPos = currentInstruction.find_last_not_of(" \r\n\t\w")
        // std::string instruction = currentInstruction.substr(pos);
        // std::cout << "Parser::dest(): " << instruction.substr(pos, destStr) << std::endl;
        // return instruction.substr(destStr);
        std::cout << "Parser::dest(): " << currentInstruction.substr(0, destStr) << " --> " << currentInstruction << std::endl;
        return currentInstruction.substr(0, destStr);
    } else
        return "null";
}


std::string Parser::comp() {
    // Returns the comp part of a C-instruction
    boost::algorithm::trim(currentInstruction);
    // std::size_t pos = currentInstruction.find_first_not_of(' ');
    // std::string instruction = currentInstruction.substr(pos);
    std::size_t destStr = currentInstruction.find('=');
    std::size_t jumpStr = currentInstruction.find(';');

    /*
        dest=comp;jump

        if string contains = and not ;
            then get everything after =
        else if string contains ; and not =
            then get everything before ;
        else if string contains ; and =
            get everything after = and before ;
    */

    // TODO: If there is a = and no ; then get everything after the =

    if (destStr != std::string::npos && jumpStr == std::string::npos) {
        // std::cout << "Parser::comp(): " << instruction.substr(++destStr) << std::endl;
        // return instruction.substr(++destStr);
        std::cout << "Parser::comp(): " << currentInstruction.substr((destStr + 1)) << " --> " << currentInstruction << std::endl;
        return currentInstruction.substr((destStr + 1));
    }

    else if (jumpStr != std::string::npos && destStr == std::string::npos) {
        // std::cout << "Parser::comp(): " << instruction.substr(0, jumpStr) << std::endl;
        // return instruction.substr(0, jumpStr);
        std::cout << "Parser::comp(): " << currentInstruction.substr(0, jumpStr) << " --> " << currentInstruction << std::endl;
        return currentInstruction.substr(0, jumpStr);
    }

    // TODO: If there is both ; and = then get everything after = and before ;
    else if (destStr != std::string::npos && jumpStr != std::string::npos) {
        std::size_t compStr = jumpStr - (destStr + 1);
        // std::cout << "Parser::comp(): " << instruction.substr(destStr, compStr) << std::endl;
        // return instruction.substr(destStr, compStr);
        std::cout << "Parser::comp(): " << currentInstruction.substr(destStr, compStr) << " --> " << currentInstruction << std::endl;
        return currentInstruction.substr(destStr, compStr);
    }

    return "\nParser::comp() error: instruction: " + currentInstruction;
}


std::string Parser::jump() {
    boost::algorithm::trim(currentInstruction);

    // Returns the jump part of a C-instruction
    std::size_t jumpStr = currentInstruction.find(';');
    // std::string::size_type ch = currentInstruction.find_last_not_of(' ');

    if (jumpStr != std::string::npos) {
        // std::cout << "Parser::jump(): " << currentInstruction.substr(++jumpStr, ch) << std::endl;
        // return currentInstruction.substr(++jumpStr, ch);
        std::cout << "Parser::jump(): " << currentInstruction.substr((jumpStr + 1)) << " --> " << currentInstruction << std::endl;
        
        return currentInstruction.substr((jumpStr + 1));
    }
    else
        return "null";
}


std::string Code::dest(const std::string &destCode) {
    const std::unordered_map<std::string, std::string> destCodeMap = {
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
        return "\nCode::dest(const std::string &destCode) error: &destCode " + destCode;
}


std::string Code::comp(const std::string &compCode) {
    const std::unordered_map<std::string, std::string> compCodeMap = {
        {"0", "0101010"},
        {"1", "0111111"},
        {"-1", "0111010"},
        {"D", "0001100"},
        {"A", "0110000"},
        {"M", "1110000"},
        {"!D", "0001101"},
        {"!A", "0110001"},
        {"!M", "1110001"},
        {"-D", "0001111"},
        {"-A", "0110011"},
        {"-M", "1110011"},
        {"D+1", "0011111"},
        {"A+1", "0110111"},
        {"M+1", "1110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"M-1", "1110010"},
        {"D+A", "0000010"},
        {"D+M", "1000010"},
        {"D-A", "0010011"},
        {"D-M", "1010011"},
        {"A-D", "0000111"},
        {"M-D", "1000111"},
        {"D&A", "0000000"},
        {"D&M", "1000000"},
        {"D|A", "0010101"},
        {"D|M", "1010101"}
    };

    std::unordered_map<std::string, std::string>::const_iterator code = compCodeMap.find(compCode);
    if (code != compCodeMap.end())
        return code->second;
    else
        return "\nCode::comp(const std::string &compCode) error: &compCode: " + compCode;
}


std::string Code::jump(const std::string &jumpCode) {
    const std::unordered_map<std::string, std::string> jumpCodeMap = {
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
        return "\nCode::jump(const std::string &jumpCode) error: &jumpCode " + jumpCode;
}