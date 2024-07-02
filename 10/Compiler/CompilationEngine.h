#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "FileOpp.h"

#ifndef COMPILATION_ENGINE
#define COMPILATION_ENGINE

class CompilationEngine {
    private:
        std::unordered_map<std::string, std::unique_ptr<std::ofstream>> outputFiles;
        std::ofstream outputFile;
        std::string currentFile;
    public:
        CompilationEngine(std::string inputFile, std::string outputFileArg);
        void compileClass();
        void compileClassVarDec();
        void compileSubroutine();
        void compileParamaterList();
        void compileVarDec();
        void compileStatements();
        void compileLet();
        void compileIf();
        void compileWhile();
        void compileDo();
        void compileReturn();
        void compileExpression();
        void compileTerm();
        int compileExpressionList();
    const std::unordered_map<std::string, std::unique_ptr<std::ofstream>>& getOutputFiles() const;
};

#endif  // COMPILATION_ENGINE