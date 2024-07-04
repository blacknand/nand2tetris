#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include "CompilationEngine.h"
#include "JackTokenizer.h"
#include "FileOpp.h"


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
        *curFileStream << "<token>" << std::endl;
        initialFileObj.compileClass();

        // while (curFileTokenizer.hasMoreTokens()) {
        //     switch (curFileTokenizer.tokenType()) {
        //         case JackTokenizer::TokenElements::KEYWORD:
        //             break;
        //         case JackTokenizer::TokenElements::INT_CONST:
        //             break;
        //         case JackTokenizer::TokenElements::STRING_CONST:
        //             break;
        //         case JackTokenizer::TokenElements::IDENTIFIER:
        //             break;
        //         case JackTokenizer::TokenElements::SYMBOL:
        //             break;
        //     }
        // } 

        *curFileStream << "</token>" << std::endl;
        curFileTokenizer.resetToken();
    }

    return 0;
}