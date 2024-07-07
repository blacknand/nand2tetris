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

        const std::string &curFileName = filePair.first;
        const std::unique_ptr<std::ofstream> &curFileStream = filePair.second;
        curFileTokenizer.initializer(curFileName);
        initialFileObj.setOutputFile(curFileName);
        initialFileObj.compileClass();
        curFileTokenizer.resetToken();
        curFileTokenizer.clearTokens();
    }

    VMWriter vmWriterTest;

    return 0;
}