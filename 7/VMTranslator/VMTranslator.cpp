// Translates Hack VM bytecode into Hack ASM

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "VMTranslator.h"


int main(int argc, char **argv) {
    Parser parser;
    std::ifstream inputFile(argv[1]);
    parser.initializer(inputFile);
    parser.getFileVect();
    parser.advance();
    parser.advance();
    parser.commandType();
    std::cout << parser.arg1() << std::endl;
    std::cout << parser.arg2() << std::endl;
    return 1;
}


void Parser::initializer(std::ifstream &inputFile) {
    std::string line;
    std::vector<std::string> lineVect;
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            lineVect.clear();
            boost::algorithm::trim(line);
            lineVect.push_back(line);
            fileVect.push_back(lineVect);
        }
        inputFile.close();
        return;
    }
    std::cout << "Failed to open file" << std::endl;
}


bool Parser::hasMoreLines() {
    int iter = (currentLine > 0) ? (currentLine + 1) : 0;

    for (int i = iter; i < fileVect.size(); i++) {
        for (int j = 0; j < fileVect[i].size(); j++) {
            std::size_t foundWhiteSpace = fileVect[i][j].find_first_not_of(" \t\n\v\f\r");
            if (fileVect[i][j].substr(foundWhiteSpace, 2) != "//")
                return true;
            continue;
        }
    }

    return false;
}


void Parser::advance() {
    int iter = (currentLine > 0) ? (currentLine + 1) : 0;

    for (int i = iter; i < fileVect.size(); i++) {
        for (int j = 0; j < fileVect[i].size(); j++) {
            std::size_t foundWhiteSpace = fileVect[i][j].find_first_not_of(" \t\n\v\f\r");
            if (foundWhiteSpace != std::string::npos) {
                if (fileVect[i][j].substr(foundWhiteSpace, 2) != "//") {
                    currentLine = i;
                    currentInstruction = fileVect[i][j];
                    return;
                } 
                continue;
            }
        }
    }
}


const std::string Parser::commandType() {
    commandMap = {
        {"add", C_ARITHMETIC},
        {"sub", C_ARITHMETIC},
        {"neq", C_ARITHMETIC},
        {"eq", C_ARITHMETIC},
        {"gt", C_ARITHMETIC},
        {"lt", C_ARITHMETIC},
        {"and", C_ARITHMETIC},
        {"or", C_ARITHMETIC},
        {"not", C_ARITHMETIC},
        {"push", C_PUSH},
        {"pop", C_POP},
        {"label", C_LABEL},
        {"goto", C_GOTO},
        {"if-goto", C_IF},
        {"function", C_CALL},
        {"return", C_RETURN}
    };

    std::size_t whitespacePos = currentInstruction.find_first_of(' ');
    std::string strippedInstruction = currentInstruction.substr(0, whitespacePos);
    std::unordered_map<std::string, Commands>::const_iterator command = commandMap.find(strippedInstruction);

    switch (command->second) {
        case 1:
            return "C_ARITHMETIC";
            break;
        case 2:
            return "C_PUSH";
            break;
        case 3:
            return "C_POP";
            break;
        case 4:
            return "C_LABEL";
            break;
        case 5:
            return "C_GOTO";
            break;
        case 6:
            return "C_IF";
            break;
        case 7:
            return "C_FUNCTION";
            break;
        case 8:
            return "C_RETURN";
            break;
        case 9:
            return "C_CALL";
            break;
    }

    return "std::string Parser::commandType() has encountered an error\n";
}


std::string Parser::arg1() {
    // C_INSTRUCTION
    std::size_t whiteSpace1 = currentInstruction.find_first_of(' ');
    if (whiteSpace1 == std::string::npos)
        return currentInstruction;

    std::string instructSubStr1 = currentInstruction.substr(whiteSpace1);
    boost::algorithm::trim(instructSubStr1);
    std::size_t whiteSpace2 = instructSubStr1.find_first_of(' ');
    std::string strippedInstruct = instructSubStr1.substr(0, whiteSpace2);    
    return strippedInstruct;
}


std::string Parser::arg2() {
    std::size_t lastWhiteSpacePos = currentInstruction.find_last_of(' ');
    std::string finalCommand = currentInstruction.substr(lastWhiteSpacePos);
    boost::algorithm::trim(finalCommand);
    return finalCommand;
}