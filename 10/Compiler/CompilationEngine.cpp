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
    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenzier.advance();

    // classVarDec*
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD && 
        (tokenizer.keyWord() == JackTokenizer::KeywordElements::STATIC ||
        tokenizer.keyWord() == JackTokenizer::KeywordElements::FIELD)) {
            compileClassVarDec();
    }

    // subroutineDec*
    if (tokenizer.tokenType() == JackTokenizer::TokenElements::KEYWORD &&
        (tokenizer.keyWord() == JackTokenizer::KeywordElements::CONSTRUCTOR ||
        tokenizer.keyWord() == JackTokenizer::KeywordElements::FUNCTION ||
        tokenizer.keyWord() == JackTokenizer::KeywordElements::METHOD)) {
            compileSubroutine();
    }

    *fileStream << "<keyword> " << tokenizer.getCurrentToken() << " </keyword>" << std::endl;
    tokenzier.advance();
}


const std::unordered_map<std::string, std::unique_ptr<std::ofstream>>& CompilationEngine::getOutputFiles() const {
    return outputFiles;
}


void CompilationEngine::setOutputFile(std::string fileName) {
    currentFile = fileName;
}