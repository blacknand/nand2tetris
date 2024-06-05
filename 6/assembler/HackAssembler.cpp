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
#include "OutFile.hpp"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./HackAssembler prog.asm" << std::endl;
        return 1;
    }

    Parser parser;
    Code code;
    SymbolTable symbolTable;
    symbolTable.initializeTable();
    parser.initializer(argv[1]);
    std::vector<std::vector<std::string>> lineVect = parser.getVect();
    int lineCounter = 0;

    for (int i = 0; i < lineVect.size(); i++) {
        for (int j = 0; j < lineVect[i].size(); j++) {
            if (parser.hasMoreLines()) {
                parser.advance();

                std::string instruction = parser.instructionType();
                std::string hackFileName = argv[0];
                int hackFileNamePos = hackFileName.find_first_not_of("./");
                hackFileName = hackFileName.substr(hackFileNamePos) + ".hack";
                OutFile hackFile(hackFileName.c_str());

                if (instruction == "C_INSTRUCTION") {
                    lineCounter++;
                    std::string instructionDest = parser.dest();
                    std::string instructionComp = parser.comp();
                    std::string instructionJump = parser.jump();
                    std::string destBinary = code.dest(instructionDest);
                    std::string compBinary = code.comp(instructionComp);
                    std::string jumpBinary = code.jump(instructionJump);
                    std::string cInstructionBinary = "111" + compBinary + destBinary + jumpBinary;
                    hackFile << cInstructionBinary << std::endl;
                } else if (instruction == "A_INSTRUCTION") {
                    lineCounter++;
                    std::string aInstruction = parser.symbol();
                    int aDigit = std::stoi(aInstruction);
                    std::string aInstructionBinary = "0" + std::bitset<15>(aDigit).to_string();
                    hackFile << aInstructionBinary << std::endl;
                } else if (instruction == "L_INSTRUCTION") {

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
    // Returns if there are any more valid lines
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
                    boost::algorithm::trim(currentInstruction);
                    return;
                } else    
                    continue;
            }
        }
    }
}


const std::string Parser::instructionType() {
    /*
        A_INSTRUCTION for @xxx, where xxx is a symbol for 
        either a decimal number or a symbol.

        C_INSTRUCTION for dest=comp;jump

        L_INSTRUCTION for (xxx), where xxx is a symbol.
    */
    if (currentInstruction[0] == '@') {
        return "A_INSTRUCTION";
    } else if (currentInstruction.find('=') != std::string::npos || currentInstruction.find(';') != std::string::npos) {
        return "C_INSTRUCTION";
    } else if (currentInstruction[0] == '(' && currentInstruction[-1] == ')') {
        return "L_INSTRUCTION";
    }

    return "\nParser::instructionType() error: instruction " + currentInstruction;
}


std::string Parser::symbol() {
    // Strips the decimal/symbol from the A/L-instruction

    if (currentInstruction[0] == '@') 
        return currentInstruction.substr(1);
    else if (currentInstruction[0] == '(' && currentInstruction[-1] == ')')
        return currentInstruction.substr(1);

    return "\nParser::symbol() error: instruction " + currentInstruction;
}


std::string Parser::dest() {
    // Returns the dest part of a C-instruction
    std::size_t destStr = currentInstruction.find('=');

    if (destStr != std::string::npos) 
        return currentInstruction.substr(0, destStr);
    else 
        return "null";
}


std::string Parser::comp() {
    // Returns the comp part of a C-instruction
    std::size_t destStr = currentInstruction.find('=');
    std::size_t jumpStr = currentInstruction.find(';');

    /*
        dest=comp;jump

        if (string contains = and not ;)
            then get everything after =
        else if (string contains ; and not =)
            then get everything before ;
        else (if string contains ; and =)
            get everything after = and before ;
    */
    if (destStr != std::string::npos && jumpStr == std::string::npos)
        return currentInstruction.substr((destStr + 1));
    else if (jumpStr != std::string::npos && destStr == std::string::npos) 
        return currentInstruction.substr(0, jumpStr);
    else if (destStr != std::string::npos && jumpStr != std::string::npos) {
        std::size_t compStr = jumpStr - (destStr + 1);
        return currentInstruction.substr(destStr, compStr);
    }

    return "\nParser::comp() error: instruction: " + currentInstruction;
}


std::string Parser::jump() {
    std::size_t jumpStr = currentInstruction.find(';');
    if (jumpStr != std::string::npos) {
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
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"MA", "101"},
        {"AD", "110"},
        {"DA", "110"},
        {"ADM", "111"},
        {"AMD", "111"},
        {"DAM", "111"},
        {"DMA", "111"},
        {"MAD", "111"},
        {"MDA", "111"},
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

/*
TODO
    SymbolTable::initializeTable()
        initialize with all predefined symbols and their addresses

        create a new valid line counter which only increments on a c or a instruction

*/

void SymbolTable::initializeTable() {
    symbolTable = {
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},
        {"R8", 8},
        {"R9", 9},
        {"R10", 10},
        {"R11", 11},
        {"R12", 12},
        {"R13", 13},
        {"R14", 14},
        {"R15", 15},
        {"SP", 0},
        {"LCL", 1},
        {"ARG", 2},
        {"THIS", 3},
        {"THAT", 4},
        {"SCREEN", 16384},
        {"KBD", 24576}
    };
}


// TODO: Add symbol entry to table
void SymbolTable::addEntry(const std::string &symbol, const int &address) {
    symbolTable.insert({symbol, address});
}


bool SymbolTable::contains(const std::string &symbol) {
    std::map<std::string, int>::iterator foundSymbol;
    foundSymbol = symbolTable.find(symbol);
    if (foundSymbol != symbolTable.end())
        return true;
    else
        return false;
}


int SymbolTable::getAddress(const std::string &symbol) {
    std::map<std::string, int>::iterator foundSymbol;
    foundSymbol = symbolTable.find(symbol);
    if (foundSymbol != symbolTable.end())
        return foundSymbol->second;
    else
        return 404;
}
// PROBLEM
    // NEED A LINE COUNTER, THAT IS ACCESSIBLE FROM ALL FUNCTIONS BUT IS NOT INSIDE ANY CLASS OR DEFINED GLOBALLY


/*
put in parser class
    can access in all methods

can then parse into the code methods
*/