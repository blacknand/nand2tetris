#include <string>
#include <iostream>
#include <unordered_map>
#include "SymbolTable.h"



SymbolTable::SymbolTable()
    : staticIndex(0), fieldIndex(0), argIndex(0), varIndex(0) {}


void SymbolTable::reset() {
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
    if (kind == "STATIC") return staticIndex;
    if (kind == "FIELD") return fieldIndex;
    if (kind == "ARG") return argIndex;
    if (kind == "VAR") return varIndex;
    return 0;
}


std::string SymbolTable::kindOf(const std::string &name) {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.kindOf;
    if (classTableCode != symbolTable.end())
        return classTableCode->second.kindOf;
    return "NONE";
}


std::string SymbolTable::typeOf(const std::string &name) {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.typeOf;
    if (classTableCode != symbolTable.end())
        return classTableCode->second.typeOf;
    return "NONE";
}


std::string SymbolTable::indexOf(const std::string &name) {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.indexOf;
    if (classTableCode != symbolTable.end())
        return classTableCode->second.indexOf;
    return -1;
}