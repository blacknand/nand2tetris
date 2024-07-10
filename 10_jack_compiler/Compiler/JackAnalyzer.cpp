#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include "CompilationEngine.h"
#include "JackTokenizer.h"
#include "FileOpp.h"
#include "SymbolTable.h"
#include "VMWriter.h"


int main(int argc, char **argv) {
    std::string inputFileArgv = argv[1];
    std::string outputFileArgv = argv[2];
    CompilationEngine initialFileObj(inputFileArgv, outputFileArgv);
    const auto &outputFiles = initialFileObj.getOutputFiles();
    for (const auto &filePair: outputFiles) {
        JackTokenizer curFileTokenizer;

        // const std::string &curFileName = filePair.first;
        // const std::unique_ptr<std::ofstream> &curFileStream = filePair.second;
        std::string curJackFile = filePair.first;
        std::string curVMFile = filePair.second;
        curFileTokenizer.initializer(curJackFile);
        initialFileObj.setOutputFile(curVMMFile);
        initialFileObj.compileClass();
        curFileTokenizer.resetToken();
        curFileTokenizer.clearTokens();
    }
    return 0;
}