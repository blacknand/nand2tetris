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
            outputFileName = (std::filesystem::path(outputFileArg) / (filePath.stem().string() + ".xml")).string();
        else if (jackFiles.size() == 1)
            outputFileName = outputFileArg;

        outputFiles[jackFile.string()] = std::make_unique<std::ofstream>(outputFileName.c_str());
    }
}


void CompilationEngine::compileClass() {
    // class className { classVarDec* subroutineDec* }
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<class>" << std::endl;

    tokenizer.advance();    // Initial token                                                                              // Get initial token
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();
    *fileStream << "<identifier>" << std::endl;
    
    // symbol table test
    *fileStream << "<name>" << tokenizer.identifier() << "</name>" << std::endl;
    *fileStream << "<category>class</category>" << std::endl;
    *fileStream << "<index>NULL</index>" << std::endl;
    *fileStream << "<usage>declared</usage>" << std::endl;

    *fileStream << " </identifier>" << std::endl;
    tokenizer.advance();
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
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

    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</class>" << std::endl;
}


void CompilationEngine::compileClassVarDec() {
    // ('static'|'field') type varName (',' varName)* ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<classVarDec>" << std::endl; 

    // ('static'|'field')
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // type
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // (',' varName)*
    while (tokenizer.getCurrentToken() == ",") {
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
        tokenizer.advance();
    }
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</classVarDec>" << std::endl; 
}


void CompilationEngine::compileSubroutine() {
    // ('constructor'|'function'|'method') ('void'|type) subroutineName '('paramaterList')' subroutineBody
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<subroutineDec>" << std::endl;

    // ('constructor'|'function'|'method')
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // (void|type)
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // subroutineName
    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // '('paramaterList')'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();
    compileParamaterList();
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // subroutineBody '{' varDec* statements '}'
    compileSubroutineBody();

    *fileStream << "</subroutineDec>" << std::endl;
}


void CompilationEngine::compileParamaterList() {
    // ((type varName) (',' type varName)*)?
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<parameterList>" << std::endl;

    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
            tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER) {
                // type
                if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
                    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
                else
                    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
                tokenizer.advance();

                // varName
                *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
                tokenizer.advance();

                // ','
                if (tokenizer.getCurrentToken() == ",") {
                    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                    tokenizer.advance();
                } else
                    break;
    }

    *fileStream << "</parameterList>" << std::endl;
}


void CompilationEngine::compileSubroutineBody() {
    // '{' varDec* statements '}'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<subroutineBody>" << std::endl;

    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();
    while (tokenizer.getCurrentToken() == "var") {
        compileVarDec();
    }
    compileStatements();
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</subroutineBody>" << std::endl;
}


void CompilationEngine::compileVarDec() {
    // 'var' type varName (',' varName)* ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<varDec>" << std::endl;

    // 'var'
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // type
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // ',' varName
    while (tokenizer.getCurrentToken() == ",") {
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();
        *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
        tokenizer.advance();
    }

    // ';'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</varDec>" << std::endl;
}


void CompilationEngine::compileStatements() {
    // statment*
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<statements>" << std::endl;

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

    *fileStream << "</statements>" << std::endl;
}


void CompilationEngine::compileLet() {
    // 'let' varName ('[' expression ']')? '=' expression ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<letStatement>" << std::endl;

    // let
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
    tokenizer.advance();

    // '[' expression ']'
    if (tokenizer.getCurrentToken() == "[") {
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();
        compileExpression();
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();
    }

    // '='
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expression
    compileExpression();

    // ';'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</letStatement>" << std::endl;
}


void CompilationEngine::compileIf() {
    // 'if' '(' expression ')' '{' statements '}' ('else' '{'statements'}')?
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<ifStatement>" << std::endl;

    // if
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // '('
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();


    // (expression)
    compileExpression();

    // ')'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // {
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // statements
    compileStatements();

    // }
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // 'else' '{'statements'}'
    if (tokenizer.getCurrentToken() == "else") {
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
        tokenizer.advance();

        // '{'
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();

        // statements
        compileStatements();

        // '}'
        *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
        tokenizer.advance();
    }

    *fileStream << "</ifStatement>" << std::endl;
}


void CompilationEngine::compileWhile() {
    // while '(' expression ')' '{' statements '}'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<whileStatement>" << std::endl;

    // while
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // '('
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expression
    compileExpression();

    // ')'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // '{'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    // statements
    compileStatements();

    // '}'
    *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
    tokenizer.advance();

    *fileStream << "</whileStatement>" << std::endl;
}


void CompilationEngine::compileDo() {
    // 'do' subroutineCall ';'
    // subroutineName '(' expressionList ')' | (className|varName) '.' subroutineName '(' expressionList ')'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<doStatement>" << std::endl;

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
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<expression>" << std::endl;

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
                *fileStream << "<symbol> " << tokenizer.symbol() << " </symbol>" << std::endl;
                tokenizer.advance();
                compileTerm();
            }

    *fileStream << "</expression>" << std::endl;
}


void CompilationEngine::compileTerm() {
    // integerConstant | stringConstant | keywordConstant | varName | varName'[' expression ']' | '(' expression ')' |
    // (unaryOp term) | subroutineCall
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<term>" << std::endl;

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
            *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
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
                    *fileStream << "<identifier> " << tokenizer.identifier() << " </identifier>" << std::endl;
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

    *fileStream << "</term>" << std::endl;
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