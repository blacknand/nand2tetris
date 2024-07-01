#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include "CompilationEngine.h"
#include "FileOpp.h"


void CompilationEngine::constructor(std::string inputFile, std::string outputFileArg) {
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

    for (const auto &jackFile: jackFiles) {
        std::filesystem::path filePath = jackFile;
        std::string outputFileName;
        if (std::filesystem::is_directory(outputFileArg))
            outputFileName = std::filesystem::path(outputFileArg) / (filePath.stem().string() + ".xml");
        else 
            outputFileName = outputFileArg;
        WriteToFile outputFile(outputFileName.c_str());
    }
}


void CompilationEngine::compileClass() {
    
}