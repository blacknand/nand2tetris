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
    tokenizer.advance();    // Initial token - keyword                                                            
    tokenizer.advance();    // className
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
    std::string kind = tokenizer.getCurrentToken(); // static or field
    tokenizer.advance(); // Advance past 'static' or 'field'

    // type
    std::string type = tokenizer.getCurrentToken();
    tokenizer.advance(); // Advance past type

    // varName
    std::string name = tokenizer.getCurrentToken();
    symbolTableClass.define(name, type, kind); // Define the first varName
    tokenizer.advance(); // Advance past varName

    // (',' varName)*
    while (tokenizer.getCurrentToken() == ",") {
        tokenizer.advance(); // Advance past ','
        name = tokenizer.getCurrentToken();
        symbolTableClass.define(name, type, kind); // Define subsequent varNames
        tokenizer.advance(); // Advance past varName
    }

    tokenizer.advance(); // Advance past ';'
}



void CompilationEngine::compileSubroutine() {
    // ('constructor'|'function'|'method') ('void'|type) subroutineName '('paramaterList')' subroutineBody
    symbolTableSubroutine.reset();
    labelInt = 0;
    whileLabelInt = 0;
    ifLabelInt = 0;

    // ('constructor'|'function'|'method')
    std::string subroutineCat = tokenizer.identifier();
    tokenizer.advance();

    // (void|type)
    std::string subroutineType;
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        subroutineType = tokenizer.getCurrentToken();
    else
        subroutineType = tokenizer.identifier();

    tokenizer.advance();    // subroutineName
    std::string subroutineName = tokenizer.identifier();
    std::string fullSubroutineName = currentClass + "." + tokenizer.identifier();
    tokenizer.advance();

    if (subroutineCat == "method")
        symbolTableSubroutine.define(currentClass + "." + tokenizer.identifier(), "this", "argument");

    // '('paramaterList')'
    tokenizer.advance();    // (
    compileParamaterList();
    tokenizer.advance();    // )

    vmWriter.writeFunction(fullSubroutineName, countNLocals());

    // Allign this with base address on which object was called upon
    if (subroutineCat == "method") {
        vmWriter.writePush("argument", 0);
        vmWriter.writePop("pointer", 0);
    } else if (subroutineCat == "constructor") {
        vmWriter.writePush("constant", symbolTableSubroutine.varCount("field"));
        vmWriter.writeCall("Memory.alloc", 1);
        vmWriter.writePush("pointer", 0);
    }

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
                tokenizer.advance();    // , or ;
                if (tokenizer.getCurrentToken() == ",")
                    tokenizer.advance();    // 
                else
                    break;
    }
}


void CompilationEngine::compileSubroutineBody() {
    // '{' varDec* statements '}'
    tokenizer.advance();    // {
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
        symbolTableSubroutine.define(tokenizer.identifier(), typeDec, "local");
        tokenizer.advance();    // varname

        if (tokenizer.getCurrentToken() == ",") 
            tokenizer.advance();    // back to varname
        else
            break;
    }
    tokenizer.advance();    // ;
}


void CompilationEngine::compileStatements() {
    // tokenizer.advance();
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

    // let varName = expression
        // save varName
        // compileExpression()
        // pop varName

    // let varName[i] = expression
        // push varName
        // compileExpression()
        // add
        // pop temp 0
        // pop pointer 1
        // push temp 0
        // pop that 0

    tokenizer.advance();    // let
    std::string varName = tokenizer.identifier();
    tokenizer.advance();    // varName
    bool isArray = false;

    // '[' expression ']'
    if (tokenizer.getCurrentToken() == "[") {
        tokenizer.advance();    // [
        if (symbolTableSubroutine.kindOf(varName) != "none") {
            vmWriter.writePush(symbolTableSubroutine.kindOf(varName), symbolTableSubroutine.indexOf(varName));
        } else {
            vmWriter.writePush(symbolTableClass.kindOf(varName), symbolTableClass.indexOf(varName));
        }
        compileExpression();
        vmWriter.writeArithmetic("add");
        tokenizer.advance();    // ]
        isArray = true;
    }

    tokenizer.advance();    // =
    compileExpression();


    if (isArray) {
        vmWriter.writePop("temp", 0);
        vmWriter.writePop("pointer", 1);
        vmWriter.writePush("temp", 0);
        vmWriter.writePop("that", 0);
    } else {
        // Find correct scope
        std::string kind;
        int index;
        if (symbolTableSubroutine.kindOf(varName) != "none") {
            kind = symbolTableSubroutine.kindOf(varName);
            index = symbolTableSubroutine.indexOf(varName);
        } else if (symbolTableClass.kindOf(varName) != "none") {
            kind = symbolTableClass.kindOf(varName);
            index = symbolTableClass.indexOf(varName);
        }
        vmWriter.writePop(kind, index);
    }
    tokenizer.advance();    // ;
}


void CompilationEngine::compileIf() {
    int currentLabel = ifLabelInt++;
    std::string trueLabel = "IF_TRUE" + std::to_string(currentLabel);
    std::string falseLabel = "IF_FALSE" + std::to_string(currentLabel);
    std::string endLabel = "IF_END" + std::to_string(currentLabel);

    tokenizer.advance();    // if
    tokenizer.advance();    // (
    compileExpression();
    tokenizer.advance();    // )

    vmWriter.writeIf(trueLabel);
    vmWriter.writeGoto(falseLabel);
    vmWriter.writeLabel(trueLabel);

    tokenizer.advance();    // {
    compileStatements();
    tokenizer.advance();    // }

    vmWriter.writeGoto(endLabel);
    vmWriter.writeLabel(falseLabel);

    // else {statements}
    if (tokenizer.getCurrentToken() == "else") {
        tokenizer.advance(); // else
        tokenizer.advance(); // {
        compileStatements();
        tokenizer.advance(); // }
    }

    vmWriter.writeLabel(endLabel);
}


void CompilationEngine::compileWhile() {
    int currentLabel = whileLabelInt++;
    std::string whileLabel = "WHILE_EXP" + std::to_string(currentLabel);
    std::string endLabel = "WHILE_END" + std::to_string(currentLabel);

    tokenizer.advance();    // while
    tokenizer.advance();    // (

    vmWriter.writeLabel(whileLabel);
    compileExpression();
    tokenizer.advance();    // )

    vmWriter.writeArithmetic("not");
    vmWriter.writeIf(endLabel);

    tokenizer.advance();    // {
    compileStatements();
    tokenizer.advance();    // }

    vmWriter.writeGoto(whileLabel);
    vmWriter.writeLabel(endLabel);
}


void CompilationEngine::compileDo() {
    // 'do' subroutineCall ';'
    // subroutineName '(' expressionList ')' | (className|varName) '.' subroutineName '(' expressionList ')'
    tokenizer.advance();    // do
    std::string mainIdentifier = tokenizer.identifier();
    tokenizer.advance();    // subroutineName or className

    int nArgs = 0;
    std::string subroutineName;
    std::string fullSubroutineName;

    if (tokenizer.getCurrentToken() == ".") {
        // Function, constructor or method call on other object
        tokenizer.advance();    // .
        subroutineName = tokenizer.identifier();
        tokenizer.advance();    // subroutineName

        std::string kind = "none";
        int index = -1;

        // Search both scope symbol tables
        if (symbolTableSubroutine.typeOf(mainIdentifier) != "none") {
            kind = symbolTableSubroutine.kindOf(mainIdentifier);
            index = symbolTableSubroutine.indexOf(mainIdentifier);
        } else if (symbolTableClass.typeOf(mainIdentifier) != "none") {
            kind = symbolTableClass.kindOf(mainIdentifier);
            index = symbolTableClass.indexOf(mainIdentifier);
        }

        if (kind != "none") {
                // Method on other object
                vmWriter.writePush(kind, index);    // Push obj reference onto stack

                if (symbolTableSubroutine.typeOf(mainIdentifier) != "none") {
                    fullSubroutineName = symbolTableSubroutine.typeOf(mainIdentifier) + "." + subroutineName;
                } else if (symbolTableClass.typeOf(mainIdentifier) != "none") {
                    fullSubroutineName = symbolTableClass.typeOf(mainIdentifier) + "." + subroutineName;
                }
                nArgs = 1;
            }
        else {
            // Static function or constructor
            fullSubroutineName = mainIdentifier + "." + subroutineName;
        }

    } else {
        // Method call on current object
        fullSubroutineName = currentClass + "." + mainIdentifier;
        vmWriter.writePush("pointer", 0);   // Push reference to current obj onto stack
        nArgs = 1;
    }

    tokenizer.advance();    // (
    nArgs += compileExpressionList();
    tokenizer.advance();    // )
    vmWriter.writeCall(fullSubroutineName, nArgs);
    vmWriter.writePop("temp", 0);
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
    else
        vmWriter.writePush("constant", 0);

    vmWriter.writeReturn();
    tokenizer.advance();    // ;
}


void CompilationEngine::compileExpression() {
    // term (op term)*
    compileTerm();  // term

    // (op term)*
    while (tokenizer.getCurrentToken() == "+" ||
            tokenizer.getCurrentToken() == "-" || 
            tokenizer.getCurrentToken() == "*" ||
            tokenizer.getCurrentToken() == "/" ||
            tokenizer.getCurrentToken() == "&" ||
            tokenizer.getCurrentToken() == "|" ||
            tokenizer.getCurrentToken() == "<" ||
            tokenizer.getCurrentToken() == ">" ||
            tokenizer.getCurrentToken() == "=") {
                std::string opToken = tokenizer.getCurrentToken();
                tokenizer.advance();    // op
                compileTerm();

                if (opToken == "+")
                    vmWriter.writeArithmetic("add");
                else if (opToken == "-")
                    vmWriter.writeArithmetic("sub");
                else if (opToken == "*")
                    vmWriter.writeCall("Math.multiply", 2);
                else if (opToken == "/")
                    vmWriter.writeCall("Math.divide", 2);
                else if (opToken == "&")
                    vmWriter.writeArithmetic("and");
                else if (opToken == "|")
                    vmWriter.writeArithmetic("or");
                else if (opToken == "<")
                    vmWriter.writeArithmetic("lt");
                else if (opToken == ">")
                    vmWriter.writeArithmetic("gt");
                else if (opToken == "=")
                    vmWriter.writeArithmetic("eq");
            }
}


void CompilationEngine::compileTerm() {
    // integerConstant | stringConstant | keywordConstant | varName | varName'[' expression ']' | '(' expression ')' |
    // (unaryOp term) | subroutineCall

    switch (tokenizer.tokenType()) {
        case JackTokenizer::TokenElements::INT_CONST: {
            vmWriter.writePush("constant", tokenizer.intVal());
            tokenizer.advance();
            break;
        }
        case JackTokenizer::TokenElements::STRING_CONST: {
            int stringLength = tokenizer.stringVal().size();
            vmWriter.writePush("constant", stringLength);
            vmWriter.writeCall("String.new", 1);
            for (auto c: tokenizer.stringVal()) {
                vmWriter.writePush("constant", hackCharacterMap.at(c));
                vmWriter.writeCall("String.appendChar", 1);
            }
            tokenizer.advance();
            break;
        }
        case JackTokenizer::TokenElements::KEYWORD: {
            if (tokenizer.getCurrentToken() == "null" || tokenizer.getCurrentToken() == "false")
                vmWriter.writePush("constant", 0);
            else if (tokenizer.getCurrentToken() == "true") {
                vmWriter.writePush("constant", 1);
                vmWriter.writeArithmetic("neg");
            } else if (tokenizer.getCurrentToken() == "this") 
                vmWriter.writePush("pointer", 0);
            tokenizer.advance();
            break;
        }
        case JackTokenizer::TokenElements::IDENTIFIER: {
            // varName
            std::string mainIdentifier = tokenizer.identifier();
            tokenizer.advance();
            if (tokenizer.getCurrentToken() == "[") {
                // varName '[' expression ']'
                tokenizer.advance();
                compileExpression();
                tokenizer.advance();

                // Push base address of array
                if (symbolTableSubroutine.kindOf(mainIdentifier) != "none")
                    vmWriter.writePush(symbolTableSubroutine.kindOf(mainIdentifier), symbolTableSubroutine.indexOf(mainIdentifier));
                else
                    vmWriter.writePush(symbolTableClass.kindOf(mainIdentifier), symbolTableClass.indexOf(mainIdentifier));

                vmWriter.writeArithmetic("add");
                vmWriter.writePop("pointer", 1);
                vmWriter.writePush("that", 0);
            } else if (tokenizer.getCurrentToken() == "(" || tokenizer.getCurrentToken() == ".") {
                // subroutineCall
                // can be constructor, method on current obj, method on other obj or static method (function)
                std::string subroutineType = mainIdentifier;
                std::string subroutineName;
                int nArgs = 0;
                if (tokenizer.getCurrentToken() == ".") {
                    tokenizer.advance();    // .
                    subroutineName = tokenizer.identifier();
                    tokenizer.advance();    // subroutineName

                    // Method/constructor call on other obj
                    if (symbolTableSubroutine.kindOf(subroutineType) != "none") {
                        vmWriter.writePush(symbolTableSubroutine.kindOf(subroutineType), symbolTableSubroutine.indexOf(subroutineType));
                        nArgs = 1;
                        subroutineType = symbolTableSubroutine.typeOf(subroutineType);
                    } else if (symbolTableClass.kindOf(subroutineType) != "none") {
                        vmWriter.writePush(symbolTableClass.kindOf(subroutineType), symbolTableClass.indexOf(subroutineType));
                        nArgs = 1;
                        subroutineType = symbolTableClass.typeOf(subroutineType);
                    }
                } else {
                    // Function call on current obj
                    subroutineName = subroutineType;
                    subroutineType = currentClass;
                    vmWriter.writePush("pointer", 0);
                    nArgs = 1;
                }

                tokenizer.advance();
                nArgs += compileExpressionList();
                tokenizer.advance();
                std::string debugStr = subroutineType + "." + subroutineName;
                vmWriter.writeCall(subroutineType + "." + subroutineName, nArgs);
            } else {
                // Push variable onto stack
                std::string kind;
                int index;
                if (symbolTableSubroutine.kindOf(mainIdentifier) != "none") {
                    kind = symbolTableSubroutine.kindOf(mainIdentifier);
                    index = symbolTableSubroutine.indexOf(mainIdentifier);
                } else if (symbolTableClass.kindOf(mainIdentifier) != "none") {
                    kind = symbolTableClass.kindOf(mainIdentifier);
                    index = symbolTableClass.indexOf(mainIdentifier);
                }
                vmWriter.writePush(kind, index);
            }
            break;
        }
        case JackTokenizer::TokenElements::SYMBOL: {
            if (tokenizer.getCurrentToken() == "(") {
                // '(' expression ')'
                tokenizer.advance();
                compileExpression();
                tokenizer.advance();
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
    // (expression (',' expression)*)?
    int nArgs = 0;
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::INT_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::STRING_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER ||
        tokenizer.getCurrentToken() == "(" ||
        tokenizer.getCurrentToken() == "-" ||
        tokenizer.getCurrentToken() == "~") {

        compileExpression();
        nArgs++;
        
        while (tokenizer.getCurrentToken() == ",") {
            tokenizer.advance();
            compileExpression();
            nArgs++;
        }
    }
    return nArgs;
}


const std::unordered_map<std::string, std::string>& CompilationEngine::getOutputFiles() const {
    return outputFiles;
}


void CompilationEngine::setOutputFile(std::string fileName) {
    currentFile = fileName;
}


int CompilationEngine::countNLocals() {
    int savedIndex = tokenizer.getCurrentIndex();
    int nLocals = 0;
    tokenizer.advance();
    while (tokenizer.getCurrentToken() == "var") {
        tokenizer.advance();
        tokenizer.advance();
        while (true) {
            nLocals++;
            tokenizer.advance();
            if (tokenizer.getCurrentToken() == ",")
                tokenizer.advance();
            else
                break;
        }
        tokenizer.advance();
    }
    tokenizer.setCurrentPos(savedIndex);

    return nLocals;
}