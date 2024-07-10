#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "CompilationEngine.h"
#include "FileOpp.h"
#include "JackAnalyzer.h"
#include "SymbolTable.h"


const std::unordered_map<char, int> CompilationEngine::hackCharacterMap = {
    {' ', 32}, {'!', 33}, {'"', 34}, {'#', 35}, {'$', 36}, {'%', 37}, 
    {'&', 38}, {'\'', 39}, {'(', 40}, {')', 41}, {'*', 42}, {'+', 43}, 
    {',', 44}, {'-', 45}, {'.', 46}, {'/', 47}, {'0', 48}, {'1', 49}, 
    {'2', 50}, {'3', 51}, {'4', 52}, {'5', 53}, {'6', 54}, {'7', 55}, 
    {'8', 56}, {'9', 57}, {':', 58}, {';', 59}, {'<', 60}, {'=', 61}, 
    {'>', 62}, {'?', 63}, {'@', 64}, {'A', 65}, {'B', 66}, {'C', 67}, 
    {'D', 68}, {'E', 69}, {'F', 70}, {'G', 71}, {'H', 72}, {'I', 73}, 
    {'J', 74}, {'K', 75}, {'L', 76}, {'M', 77}, {'N', 78}, {'O', 79}, 
    {'P', 80}, {'Q', 81}, {'R', 82}, {'S', 83}, {'T', 84}, {'U', 85}, 
    {'V', 86}, {'W', 87}, {'X', 88}, {'Y', 89}, {'Z', 90}, {'[', 91}, 
    {'\\', 92}, {']', 93}, {'^', 94}, {'_', 95}, {'`', 96}, {'a', 97}, 
    {'b', 98}, {'c', 99}, {'d', 100}, {'e', 101}, {'f', 102}, {'g', 103}, 
    {'h', 104}, {'i', 105}, {'j', 106}, {'k', 107}, {'l', 108}, {'m', 109}, 
    {'n', 110}, {'o', 111}, {'p', 112}, {'q', 113}, {'r', 114}, {'s', 115}, 
    {'t', 116}, {'u', 117}, {'v', 118}, {'w', 119}, {'x', 120}, {'y', 121}, 
    {'z', 122}, {'{', 123}, {'|', 124}, {'}', 125}, {'~', 126}
};


CompilationEngine::CompilationEngine(std::string inputFile, std::string outputFileArg) {
    std::filesystem::path inputPath(inputFile);
    std::vector<std::filesystem::path> jackFiles;

    if (std::filesystem::is_directory(inputPath)) {
        for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(inputPath)) {
            if (dirEntry.is_regular_file() && dirEntry.path().extension() == ".jack") 
                jackFiles.push_back(dirEntry.path());
        }
    } else if (inputPath.extension() == ".jack") 
        jackFiles.push_back(inputPath);

    if (std::filesystem::is_directory(outputFileArg) || jackFiles.size() > 1) {
        if (!std::filesystem::exists(outputFileArg))
            std::filesystem::create_directories(outputFileArg);
    }

    for (const auto &jackFile : jackFiles) {
        std::filesystem::path filePath = jackFile;
        std::string outputFileName;

        if (std::filesystem::is_directory(outputFileArg))
            outputFileName = (std::filesystem::path(outputFileArg) / (filePath.stem().string() + ".vm")).string();
        else if (jackFiles.size() == 1)
            outputFileName = outputFileArg;

        outputFiles[jackFile.string()] = outputFileName;
    }
}


void CompilationEngine::compileClass() {
    // class className { classVarDec* subroutineDec* }
    vmWriter.initializer(currentFile);
    symbolTableClass.reset();

    tokenizer.advance();    // Initial token                                                                           
    tokenizer.advance();    // Identifier
    // tokenizer.advance();    // Class name
    currentClass = tokenizer.identifier();
    tokenizer.advance();    // {
    tokenizer.advance();

    // classVarDec*
    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD && 
           (tokenizer.keyWord() == JackTokenizer::KeywordElements::STATIC ||
            tokenizer.keyWord() == JackTokenizer::KeywordElements::FIELD)) {
        compileClassVarDec();
    }

    // subroutineDec*
    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD &&
           (tokenizer.keyWord() == JackTokenizer::KeywordElements::CONSTRUCTOR ||
            tokenizer.keyWord() == JackTokenizer::KeywordElements::FUNCTION ||
            tokenizer.keyWord() == JackTokenizer::KeywordElements::METHOD)) {
        compileSubroutine();
    }

    tokenizer.advance();    // }
}


void CompilationEngine::compileClassVarDec() {
    // ('static'|'field') type varName (',' varName)* ';'

    // ('static'|'field')
    std::string cat = tokenizer.getCurrentToken();
    tokenizer.advance();

    // type
    std::string typeDec;
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        typeDec = tokenizer.getCurrentToken();
    else
        typeDec = tokenizer.identifier();
    tokenizer.advance();

    // varname (',' varName)*
    while (true) {
        // std::transform(cat.begin(), cat.end(), cat.begin(), ::toupper);
        symbolTableClass.define(tokenizer.identifier(), typeDec, cat);
        tokenizer.advance();
        if (tokenizer.getCurrentToken() == ",")
            tokenizer.advance();
        else
            break;
    }
    tokenizer.advance();
}


void CompilationEngine::compileSubroutine() {
    // ('constructor'|'function'|'method') ('void'|type) subroutineName '('paramaterList')' subroutineBody

    symbolTableSubroutine.reset();

    // ('constructor'|'function'|'method')
    std::string subroutineType = tokenizer.identifier();
    tokenizer.advance();

    // (void|type)
    std::string cat = (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD) ?
            tokenizer.getCurrentToken() : tokenizer.identifier();
    tokenizer.advance();

    // subroutineName
    std::string subroutineName = tokenizer.identifier();
    tokenizer.advance();

    // '('paramaterList')'
    tokenizer.advance();        // (
    compileParamaterList();
    tokenizer.advance();        // )

    if (subroutineType == "method") {
        vmWriter.writeFunction(currentClass + "." + subroutineName, symbolTableSubroutine.varCount("var"));
        vmWriter.writePush("argument", 0);
        vmWriter.writePop("pointer", 0);
    } else if (subroutineType == "constructor") {
        int nFields = symbolTableClass.varCount("field");
        vmWriter.writeFunction(currentClass + "." + subroutineName, symbolTableSubroutine.varCount("var"));
        vmWriter.writePush("constant", nFields);
        vmWriter.writeCall("Memory.alloc", 1);
        vmWriter.writePop("pointer", 0);            // THIS = base address returned by alloc
    } else
        vmWriter.writeFunction(currentClass + "." + subroutineName, symbolTableSubroutine.varCount("var"));
    
    // subroutineBody '{' varDec* statements '}'
    compileSubroutineBody();
}


void CompilationEngine::compileParamaterList() {
    // ((type varName) (',' type varName)*)?
    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
            tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER) {
                // type
                std::string typeDec;
                if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
                    typeDec = tokenizer.getCurrentToken();
                else
                    typeDec = tokenizer.identifier();
                tokenizer.advance();

                // varName
                symbolTableSubroutine.define(tokenizer.identifier(), typeDec, "argument");
                tokenizer.advance();

                // ','
                if (tokenizer.getCurrentToken() == ",")
                    tokenizer.advance();
                else
                    break;
    }
}


void CompilationEngine::compileSubroutineBody() {
    // '{' varDec* statements '}'

    while (tokenizer.getCurrentToken() == "var") {
        compileVarDec();
    }
    compileStatements();
    tokenizer.advance();    // }
}


void CompilationEngine::compileVarDec() {
    // 'var' type varName (',' varName)* ';'
    tokenizer.advance();    // var

    // type
    std::string typeDec;
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD) 
        typeDec = tokenizer.getCurrentToken();
    else
        typeDec = tokenizer.identifier();
    tokenizer.advance();

    // varname (',' varName)*
    while (true) {
        symbolTableSubroutine.define(tokenizer.identifier(), typeDec, "var");
        tokenizer.advance();

        if (tokenizer.getCurrentToken() == ",")
            tokenizer.advance();
        else
            break;
    }

    tokenizer.advance();    // ;
}


void CompilationEngine::compileStatements() {
    // statment*
    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD) {
        if (tokenizer.keyWord() == JackTokenizer::KeywordElements::LET)
            compileLet();
        else if (tokenizer.keyWord() == JackTokenizer::KeywordElements::IF)
            compileIf();
        else if (tokenizer.keyWord() == JackTokenizer::KeywordElements::WHILE)
            compileWhile();
        else if (tokenizer.keyWord() == JackTokenizer::KeywordElements::DO)
            compileDo();
        else if (tokenizer.keyWord() == JackTokenizer::KeywordElements::RETURN)
            compileReturn();
    }
}


void CompilationEngine::compileLet() {
    // 'let' varName ('[' expression ']')? '=' expression ';'
    tokenizer.advance();    // let
    std::string varName = tokenizer.identifier();    // varName
    tokenizer.advance();

    // '[' expression ']'
    if (tokenizer.getCurrentToken() == "[") {
        // Array access: let varName[expression1] = expression2;
        // tokenizer.advance();    // [
        auto [kind, index] = getVariableInfo(varName);
        vmWriter.writePush(kind, index, "// compileLet, line 259: " + varName);
        tokenizer.advance();
        compileExpression();
        tokenizer.advance();    // ]
        vmWriter.writeArithmetic("add");
        tokenizer.advance();    // =
        compileExpression();
        vmWriter.writePop("temp", 0);       // temp 0 = expression 2
        vmWriter.writePop("pointer", 1);    // pointer 1 = *(arr + expression 1)
        vmWriter.writePush("temp", 0);      // push expression 2 onto stack
        vmWriter.writePop("that", 0);       // *(arr + expression 1) = expression 2

    } else {
        tokenizer.advance();    // =
        compileExpression();
        auto [kind, index] = getVariableInfo(varName);
        vmWriter.writePop(kind, index, "// compileLet, line 273: " + varName);
    }
    tokenizer.advance();    // ;
}


void CompilationEngine::compileIf() {
    static int ifLabelInt = 0;
    int currentIfLabelInt = ifLabelInt++;   // Use a separate variable to ensure unique labels within the function
    std::string labelTrue = "IF_TRUE" + std::to_string(currentIfLabelInt);
    std::string labelFalse = "IF_FALSE" + std::to_string(currentIfLabelInt);
    std::string labelEnd = "IF_END" + std::to_string(currentIfLabelInt);

    // 'if' '(' expression ')' '{' statements '}' ('else' '{'statements'}')?
    tokenizer.advance();    // 'if'
    tokenizer.advance();    // '('
    compileExpression();    
    tokenizer.advance();    // ')'
    
    vmWriter.writeArithmetic("not");
    vmWriter.writeIf(labelFalse);
    
    tokenizer.advance();    // '{'
    compileStatements();    
    tokenizer.advance();    // '}'

    vmWriter.writeGoto(labelEnd);       // goto L2 (end)
    vmWriter.writeLabel(labelFalse);    // label L1 (false label)

    // 'else' '{' statements '}'
    if (tokenizer.getCurrentToken() == "else") {
        tokenizer.advance();    // 'else'
        tokenizer.advance();    // '{'
        compileStatements();    
        tokenizer.advance();    // '}'
    }

    vmWriter.writeLabel(labelEnd); 
}



void CompilationEngine::compileWhile() {
    static int whileLabelInt = 0;
    int currentWhileLabelInt = whileLabelInt++;     // Use a separate variable to ensure unique labels within the function

    std::string labelStart = "WHILE_EXP" + std::to_string(currentWhileLabelInt);
    std::string labelEnd = "WHILE_END" + std::to_string(currentWhileLabelInt);

    // 'while' '(' expression ')' '{' statements '}'
    tokenizer.advance();    // 'while'
    tokenizer.advance();    // '('

    vmWriter.writeLabel(labelStart);    // label L1
    compileExpression(); 
    tokenizer.advance();                // ')'

    vmWriter.writeArithmetic("not");
    vmWriter.writeIf(labelEnd);         // if-goto L2

    tokenizer.advance();    // '{'
    compileStatements(); 
    tokenizer.advance();    // '}'

    vmWriter.writeGoto(labelStart);     // goto L1
    vmWriter.writeLabel(labelEnd);      // label L2
}



void CompilationEngine::compileDo() {
    // 'do' subroutineCall ';'
    // subroutineName '(' expressionList ')' | (className|varName) '.' subroutineName '(' expressionList ')'
    tokenizer.advance();    // do
    tokenizer.advance();    // subroutineName
    if (tokenizer.getCurrentToken() == ".") {
        tokenizer.advance();    // .
        tokenizer.advance();    // subroutineName
    }
    tokenizer.advance();    // (
    compileExpressionList();
    tokenizer.advance();    // )
    tokenizer.advance();    // ;
}


void CompilationEngine::compileReturn() {
    // 'return' expression? ';'
    tokenizer.advance();    // return

    // expression?
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::INT_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::STRING_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER ||
        tokenizer.getCurrentToken() == "(" ||
        tokenizer.getCurrentToken() == "-" ||
        tokenizer.getCurrentToken() == "~")
            compileExpression();

    vmWriter.writeReturn();
    tokenizer.advance();    // ;
}


void CompilationEngine::compileExpression() {
    // term (op term)*

    // term
    compileTerm();

    // (op term)*
    while (tokenizer.getCurrentToken() == "+" ||
            tokenizer.getCurrentToken() == "-" || 
            tokenizer.getCurrentToken() == "*" ||
            tokenizer.getCurrentToken() == "/" ||
            tokenizer.getCurrentToken() == "&amp;" ||
            tokenizer.getCurrentToken() == "|" ||
            tokenizer.getCurrentToken() == "&lt;" ||
            tokenizer.getCurrentToken() == "&gt;" ||
            tokenizer.getCurrentToken() == "=") {
                tokenizer.advance();
                compileTerm();
            }
}


void CompilationEngine::compileTerm() {
    // integerConstant | stringConstant | keywordConstant | varName | varName'[' expression ']' | '(' expression ')' |
    // (unaryOp term) | subroutineCall

    switch (tokenizer.tokenType()) {
        case JackTokenizer::TokenElements::INT_CONST: {
            vmWriter.writePush("constant", tokenizer.intVal());
            tokenizer.advance();    // might advance too much
            break;
        }
        case JackTokenizer::TokenElements::STRING_CONST: {
            int strLength = tokenizer.stringVal().length();
            vmWriter.writePush("constant", strLength);
            vmWriter.writeCall("String.new", 1);
            for (auto c: tokenizer.stringVal()) {
                int asciiVal = hackCharacterMap.at(c);
                vmWriter.writePush("constant", asciiVal);
                vmWriter.writeCall("String.appendChar", 1);
            }
            tokenizer.advance();
            break;
        }
        case JackTokenizer::TokenElements::KEYWORD: {
            // *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
            std::string keyword = tokenizer.identifier();
            if (keyword == "null" || keyword == "false")
                vmWriter.writePush("constant", 0);
            else if (keyword == "true") {
                vmWriter.writePush("constant", 1);
                vmWriter.writeArithmetic("neg");
            } else if (keyword == "this")
                vmWriter.writePush("pointer", 0);
            tokenizer.advance();
            break;
        }
        case JackTokenizer::TokenElements::IDENTIFIER: {
            std::string curIdentifier = tokenizer.identifier();     // varName
            tokenizer.advance();
            if (tokenizer.getCurrentToken() == "[") {
                // varName '[' expression ']'
                auto [kind, index] = getVariableInfo(curIdentifier);
                vmWriter.writePush(kind, index, "// compileTerm, line 441: " + curIdentifier);
                tokenizer.advance();
                compileExpression();
                tokenizer.advance();
                vmWriter.writeArithmetic("add");
            } else if (tokenizer.getCurrentToken() == "(") {
                // Method call on current object
                std::string subroutineName = currentClass + "." + curIdentifier;
                vmWriter.writePush("pointer", 0);
                tokenizer.advance();
                int nArgs = compileExpressionList() + 1;
                tokenizer.advance();
                vmWriter.writeCall(subroutineName, nArgs);
            } else if (tokenizer.getCurrentToken() == ".") {
                // External method or function call
                tokenizer.advance();
                std::string methodName = tokenizer.identifier();
                tokenizer.advance();
                tokenizer.advance();
                std::string subroutineName;
                int nArgs = 0;

                auto [kind, index] = getVariableInfo(curIdentifier);
                if (kind != "none") {
                    // Method call on other object
                    vmWriter.writePush(kind, index, "// compileTerm, line 465: " + curIdentifier);
                    subroutineName = symbolTableSubroutine.typeOf(curIdentifier) + "." + methodName;
                    nArgs = compileExpressionList() + 1;
                } else  {
                    // Regular function call
                    subroutineName = curIdentifier + "." + methodName;
                    nArgs = compileExpressionList();
                } 
                tokenizer.advance();
                vmWriter.writeCall(subroutineName, nArgs);
            } else {
                // Attribute access
                auto [kind, index] = getVariableInfo(curIdentifier);
                if (kind != "none") 
                    vmWriter.writePush(kind, index, "// compileTerm, line 490: " + curIdentifier);
            }
            break;
        }
        case JackTokenizer::TokenElements::SYMBOL: {
            if (tokenizer.getCurrentToken() == "(") {
                // '(' expression ')'
                tokenizer.advance();
                compileExpression();
                tokenizer.advance();    // FUCK
            } else if (tokenizer.getCurrentToken() == "-" || tokenizer.getCurrentToken() == "~") {
                // unaryOp term
                std::string op = tokenizer.getCurrentToken();
                tokenizer.advance();
                compileTerm();
                if (op == "-")
                    vmWriter.writeArithmetic("neg");
                else if (op == "~")
                    vmWriter.writeArithmetic("not");
            } 
            break;
        }
    }
}


int CompilationEngine::compileExpressionList() {
    int nArgs = 0;
    std::cout << "Entering compileExpressionList with token: " << tokenizer.getCurrentToken() << std::endl;
    if (tokenizer.getCurrentToken() != ")") {
        compileExpression();
        nArgs++;
        
        // Continue processing expressions separated by commas
        while (tokenizer.getCurrentToken() == ",") {
            std::cout << "Found comma, advancing..." << std::endl;
            tokenizer.advance();  
            compileExpression();
            nArgs++;
        }
    }
    std::cout << "Leaving compileExpressionList with token: " << tokenizer.getCurrentToken() << std::endl;
    return nArgs;
}



const std::unordered_map<std::string, std::string> &CompilationEngine::getOutputFiles() const {
    return outputFiles;
}


void CompilationEngine::setOutputFile(std::string fileName) {
    currentFile = fileName;
}


std::pair<std::string, int> CompilationEngine::getVariableInfo(const std::string &varName) {
    std::string kind = symbolTableSubroutine.kindOf(varName);
    int index = symbolTableSubroutine.indexOf(varName);

    if (kind == "none") {
        kind = symbolTableClass.kindOf(varName);
        index = symbolTableClass.indexOf(varName);
    }

    if (kind == "field") 
        kind = "this";
    else if (kind == "var")
        kind = "local";

    // std::transform(kind.begin(), kind.end(), kind.begin(), ::tolower);
    return {kind, index};
}
