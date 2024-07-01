#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef COMPILATION_ENGINE
#define COMPILATION_ENGINE

class CompilationEngine {
    public:
        void constructor(std::string inputFile, std::string outputFile);
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
        
};

#endif  // COMPILATION_ENGINE