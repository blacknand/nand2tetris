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

    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
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

    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void CompilationEngine::compileClassVarDec() {
    // ('static'|'field') type varName (',' varName)* ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // ('static'|'field')
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // type
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // (',' varName)*
    while (tokenizer.getCurrentToken() == ",") {
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
        tokenizer.advance();
    }
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void CompilationEngine::compileSubroutine() {
    // ('constructor'|'function'|'method') ('void'|type) subroutineName '('paramaterList')' subroutineBody
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // ('constructor'|'function'|'method')
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // (void|type)
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // subroutineName
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // '('paramaterList')'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
    compileParamaterList();
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // subroutineBody '{' varDec* statements '}'
    compileSubroutineBody();
}


void CompilationEngine::compileParamaterList() {
    // ((type varName) (',' type varName)*)?
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    while (tokenzier.tokenType() == JackTokenizer::TokenElements::KEYWORD ||
            tokenizer.tokenType() == JackTokenizer::TokenElements::IDENTIFIER) {
                // type
                if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
                    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
                else
                    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
                tokenizer.advance();

                // varName
                *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
                tokenizer.advance();

                // ','
                if (tokenizer.getCurrentToken() == ",") {
                    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
                    tokenizer.advance();
                } else
                    break;
    }
}


void CompilationEngine::compileSubroutineBody() {
    // '{' varDec* statements '}'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
    while (tokenizer.getCurrentToken() == "var") {
        compileVarDec();
    }
    compileStatements();
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void CompilationEngine::compileVarDec() {
    // 'var' type varName (',' varName)* ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // 'var'
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // type
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD)
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    else
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // ',' varName
    while (tokenizer.getCurrentToken() == ",") {
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
        tokenizer.advance();
    }

    // ';'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void CompilationEngine::compileStatements() {
    // statment*
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    while (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD) {
        if (tokenizer.keyWord() == JackTokenizer::KeywordElements::LET)
            compileLet();
        else if (tokenizer.keyWord == JackTokenizer::KeywordElements::IF)
            compileIf();
        else if (tokenizer.keyWord == JackTokenizer::KeywordElements::WHILE)
            compileWhile();
        else if (tokenizer.keyWord == JackTokenizer::KeywordElements::DO)
            compileDo();
        else if (tokenizer.keyWord == JackTokenizer::KeywordElements::RETURN)
            compileReturn();
    }
}


void CompilationEngine::compileLet() {
    // 'let' varName ('[' expression ']')? '=' expression ';'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // let
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // varName
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    // '[' expression ']'
    if (tokenizer.getCurrentToken() == "[") {
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();
        compileExpression();
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();
    }

    // '='
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expression
    compileExpression();

    // ';'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void CompilationEngine::compileIf() {
    // 'if' '(' expression ')' '{' statements '}' ('else' '{'statements'}')?
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // if
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // '('
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();


    // (expression)
    compileExpression();

    // ')'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // {
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // statements
    compileStatement();

    // }
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // 'else' '{'statements'}'
    if (tokenizer.getCurrentToken() == "else") {
        *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
        tokenizer.advance();

        // '{'
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();

        // statements
        compileStatements();

        // '}'
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();
    }
}


void CompilationEngine::compileWhile() {
    // while '(' expression ')' '{' statements '}'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // while
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // '('
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expression
    compileExpression();

    // ')'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // '{'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // statements
    compileStatements();

    // '}'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


void compileDo() {
    // 'do' subroutineCall ';'
    // subroutineName '(' expressionList ')' | (className|varName) '.' subroutineName '(' expressionList ')'
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>>::const_iterator currentFileObj = outputFiles.find(currentFile);
    const std::unique_ptr<std::ofstream> &fileStream = currentFileObj->second;

    // do
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenizer.advance();

    // subroutineName
    *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
    tokenizer.advance();

    if (tokenizer.getCurrentToken() == ".") {
        // .
        *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
        tokenizer.advance();

        // subroutineName
        *fileStream << "<identifier> " << tokenizer.getCurrentToken() << " </identifier>" << std::endl;
        tokenizer.advance();
    }

    // (
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // expressionList
    compileExpressionList();

    // )
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();

    // ';'
    *fileStream << "<symbol> " << tokenizer.getCurrentToken() << " </symbol>" << std::endl;
    tokenizer.advance();
}


const std::unordered_map<std::string, std::unique_ptr<std::ofstream>>& CompilationEngine::getOutputFiles() const {
    return outputFiles;
}


void CompilationEngine::setOutputFile(std::string fileName) {
    currentFile = fileName;
}