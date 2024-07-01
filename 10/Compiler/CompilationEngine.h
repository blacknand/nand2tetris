#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "FileOpp.h"

#ifndef COMPILATION_ENGINE
#define COMPILATION_ENGINE

class CompilationEngine {
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
    private:
        WriteToFile fileObj;
        std::ofstream outputFile;
};

#endif  // COMPILATION_ENGINE