#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include "CompilationEngine.h"
#include "FileOpp.h"


CompilationEngine::CompilationEngine(std::string inputFile, std::string outputFileArg) {
    std::filesystem::path inputPath(inputFile);
    std::vector<std::filesystem::path> jackFiles;

    if (std::filesystem::is_directory(inputPath)) {
        for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(inputPath)) {
            if (dirEntry.is_regular_file() && dirEntry.path().extension() == ".jack") {
                jackFiles.push_back(dirEntry.path());
            }
        }
    } else if (inputPath.extension() == ".jack") 
        jackFiles.push_back(inputPath);

    if (std::filesystem::is_directory(outputFileArg) || jackFiles.size() > 1) {
        if (!std::filesystem::exists(outputFileArg)) {
            std::filesystem::create_directories(outputFileArg);
        }
    }


    for (const auto &jackFile : jackFiles) {
        std::filesystem::path filePath = jackFile;
        std::string outputFileName;

        if (std::filesystem::is_directory(outputFileArg)) {
            outputFileName = (std::filesystem::path(outputFileArg) / (filePath.stem().string() + ".xml")).string();
        } else if (jackFiles.size() == 1) {
            outputFileName = outputFileArg;
        } else {
            std::cerr << "When processing multiple .jack files, output must be a directory." << std::endl;
            return;
        }

        outputFile = fileObj.fileWriter(outputFileName.c_str());

    }
}


void CompilationEngine::compileClass() {
    
}