#include <string>
#include <iostream>
#include <unordered_map>
#include "SymbolTable.h"



SymbolTable::SymbolTable()
    : staticIndex(0), fieldIndex(0), argIndex(0), varIndex(0) {}


void SymbolTable::SymbolTable() {
    symbolTableClass.clear();
    symbolTableSubroutine.clear();
    staticIndex = 0, fieldIndex = 0, argIndex = 0, varIndex = 0;
}


void SymbolTable::define(const std::string &name, const std::string &type, const std::string &kind) {
    if (kind == "STATIC") {
        symbolTable[name]({type, kind, staticIndex});
        staticIndex++;
    } else if (kind == "FIELD") {
        symbolTable[name]({type, kind, fieldIndex});
        fieldIndex++;
    } else if (kind == "ARG") {
        symbolTable[name]({type, kind, argIndex});
        argIndex++;
    } else if (kind == "VAR") {
        symbolTable[name]({type, kind, varIndex});
        varIndex++;
    }
} 


int SymbolTable::varCount(const std::string &kind) {
    // std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator code = symbolTable.find(name);
    // if (code != symbolTable.end())
    //     return code->second;
    if (kind == "STATIC") return staticIndex;
    if (kind == "FIELD") return fieldIndex;
    if (kind == "ARG") return argIndex;
    if (kind == "VAR") return varIndex;
    return 0;
}

