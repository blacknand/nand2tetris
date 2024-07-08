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
    VMWriter vmWriter(currentFile);     // Set current VM file to write to
    symbolTableClass.reset();

    tokenizer.advance();    // Initial token                                                                           
    tokenizer.advance();    // Identifier
    tokenizer.advance();    // Class name
    currentFunction = tokenizer.identifier();
    tokenizer.advance();    // {

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
        std::transform(cat.begin(), cat.end(), cat.begin(), ::toupper);
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
    std::string subroutineType = tokenizer.keyWord();
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

    // subroutineBody '{' varDec* statements '}'
    compileSubroutineBody();

    int subroutineLocalVars = symbolTableClass.varCount("VAR");
    vmWriter.writeFunction(currentClass + "." + subroutineName, subroutineLocalVars);

    if (subroutineType == "method") {
        symbolTableSubroutine.define((currentClass + "." + subroutineName), "this", "ARG");
        // Align virtual mem segment w base address of object of which the method was called
        vmWriter.writePush("argument", 0);
        vmWriter.writePop("pointer", 0);
    } else if (subroutineType == "constructor") {
        int nFields = symbolTableClass.varCount("FIELD");
        vmWriter.writePush("constant", nFields);
        vmWriter.writeCall("Memory.alloc", 1);
        vmWriter.writePop("pointer", 1);
        vmWriter.writePush("pointer", 0);
        vmWriter.writeReturn();
    }
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
                symbolTableSubroutine.define(tokenizer.identifier(), typeDec, "ARG");
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
        symbolTableSubroutine.define(tokenizer.identifier(), typeDec, "VAR");
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

    tokenizer.advance();    // varName

    // '[' expression ']'
    if (tokenizer.getCurrentToken() == "[") {
        tokenizer.advance();    // [
        compileExpression();
        tokenizer.advance();    // ]
    }

    tokenizer.advance();    // =

    // expression
    compileExpression();

    tokenizer.advance();    // ;
}


void CompilationEngine::compileIf() {
    // 'if' '(' expression ')' '{' statements '}' ('else' '{'statements'}')?
    tokenizer.advance();    // if
    tokenizer.advance();    // (
    compileExpression();
    tokenizer.advance();    // )
    tokenizer.advance();    // {
    compileStatements();
    tokenizer.advance();    // }

    // 'else' '{'statements'}'
    if (tokenizer.getCurrentToken() == "else") {
        tokenizer.advance();    // else
        tokenizer.advance();    // {
        compileStatements();
        tokenizer.advance();    // }
    }
}


void CompilationEngine::compileWhile() {
    // while '(' expression ')' '{' statements '}'
    tokenizer.advance();    // while
    tokenizer.advance();    // (
    compileExpression();
    tokenizer.advance();    // )
    tokenizer.advance();    // {
    compileStatements();
    tokenizer.advance();    // }
}


void CompilationEngine::compileDo() {
    // 'do' subroutineCall ';'
    // subroutineName '(' expressionList ')' | (className|varName) '.' subroutineName '(' expressionList ')'

    // do
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // subroutineName
    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    if (tokenizer.getCurrentToken() == ".") {
        // .
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();

        // subroutineName
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
        tokenizer.advance();
    }

    // (
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expressionList
    compileExpressionList();

    // )
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // ';'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</doStatement>" << std::endl;
}


void CompilationEngine::compileReturn() {
    // 'return' expression? ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<returnStatement>" << std::endl;

    // return
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // expression?
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::INT_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::STRING_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER ||
        tokenizer.getCurrentToken() == "(" ||
        tokenizer.getCurrentToken() == "-" ||
        tokenizer.getCurrentToken() == "~")
            compileExpression();

    // ';'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</returnStatement>" << std::endl;
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
        case JackTokenizer::TokenElements::INT_CONST:
            *fileStream << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << std::endl;
            tokenizer.advance();
            break;
        case JackTokenizer::TokenElements::STRING_CONST:
            *fileStream << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << std::endl;
            tokenizer.advance();
            break;
        case JackTokenizer::TokenElements::KEYWORD:
            *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
            tokenizer.advance();
            break;
        case JackTokenizer::TokenElements::IDENTIFIER:
            // varName
            *fileStream << "<identifier>" << std::endl;
            *fileStream << "<name>" << tokenizer.identifier() << "</name>" << std::endl;
            *fileStream << "<category>" << symbolTableClass.kindOf(tokenizer.identifier()) << "</category>" << std::endl;
            *fileStream << "<index>" << symbolTableClass.indexOf(tokenizer.identifier()) << "</index>" << std::endl;
            *fileStream << "<usage>used</usage>" << std::endl;
            *fileStream << "</identifier>" << std::endl;
            tokenizer.advance();
            if (tokenizer.getCurrentToken() == "[") {
                // varName '[' expression ']'
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
                compileExpression();
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
            } else if (tokenizer.getCurrentToken() == "(" || tokenizer.getCurrentToken() == ".") {
                // subroutineCall
                if (tokenizer.getCurrentToken() == ".") {
                    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                    tokenizer.advance();
                    // *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
                    *fileStream << "<identifier>" << std::endl;
                    *fileStream << "<name>" << tokenizer.identifier() << "</name>" << std::endl; 
                    *fileStream << "<category>subroutine</category>" << std::endl;
                    *fileStream << "<index>NULL</index>" << std::endl;
                    *fileStream << "<usage>used</usage>" << std::endl; 
                    *fileStream << "</identifier>" << std::endl;
                    tokenizer.advance();
                }
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
                compileExpressionList();
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
            }
            break;
        case JackTokenizer::TokenElements::SYMBOL:
            if (tokenizer.getCurrentToken() == "(") {
                // '(' expression ')'
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
                compileExpression();
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
            } else if (tokenizer.getCurrentToken() == "-" || tokenizer.getCurrentToken() == "~") {
                // unaryOp term
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
                compileTerm();
            } 
            break;
    }
}


int CompilationEngine::compileExpressionList() {
    // (expression (',' expression)*)?
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;
    int returnInt = 0;

    *fileStream << "<expressionList>" << std::endl;

    if (tokenizer.tokenType() == JackTokenizer::TokenElements::INT_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::STRING_CONST ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
        tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER ||
        tokenizer.getCurrentToken() == "(" ||
        tokenizer.getCurrentToken() == "-" ||
        tokenizer.getCurrentToken() == "~") {

        compileExpression();
        returnInt++;
        
        while (tokenizer.getCurrentToken() == ",") {
            *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
            tokenizer.advance();
            compileExpression();
            returnInt++;
        }
    }

    *fileStream << "</expressionList>" << std::endl;

    return returnInt;
}


const std::unordered_map<std::string, std::unique_ptr<std::ofstream>>& CompilationEngine::getOutputFiles() const {
    return outputFiles;
}


void CompilationEngine::setOutputFile(std::string fileName) {
    currentFile = fileName;
}