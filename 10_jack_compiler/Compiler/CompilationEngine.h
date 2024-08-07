#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "FileOpp.h"
#include "JackTokenizer.h"
#include "SymbolTable.h"
#include "VMWriter.h"

#ifndef COMPILATION_ENGINE
#define COMPILATION_ENGINE

class CompilationEngine {
    private:
        static const std::unordered_map<char, int> hackCharacterMap;
        std::unordered_map<std::string, std::string> outputFiles;
        std::string currentFile;
        JackTokenizer tokenizer;
        SymbolTable symbolTableClass;
        SymbolTable symbolTableSubroutine;
        VMWriter vmWriter;
        std::string currentClass;
        std::string currentFunction;
        std::string currentFullSubroutineName;
        int labelInt = 0;
        int whileLabelInt = 0;
        int ifLabelInt = 0;
    public:
        CompilationEngine(std::string inputFile, std::string outputFileArg);
        void compileClass();
        void compileClassVarDec();
        void compileSubroutine();
        void compileParamaterList();
        void compileSubroutineBody();
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
        const std::unordered_map<std::string, std::string>& getOutputFiles() const;
        void setOutputFile(std::string fileName);
        int countNLocals();
};

#endif  // COMPILATION_ENGINE