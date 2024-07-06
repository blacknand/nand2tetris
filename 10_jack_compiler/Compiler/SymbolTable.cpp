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
        symbolTableClass[name] = {type, kind, staticIndex};
        staticIndex++;
    } else if (kind == "FIELD") {
        symbolTableClass[name] = {type, kind, fieldIndex} ;
        fieldIndex++;
    } else if (kind == "ARG") {
        symbolTableSubroutine[name] = {type, kind, argIndex};
        argIndex++;
    } else if (kind == "VAR") {
        symbolTableSubroutine[name] = {type, kind, varIndex};
        varIndex++;
    }
} 


int SymbolTable::varCount(const std::string &kind) const {
    if (kind == "STATIC") return staticIndex;
    if (kind == "FIELD") return fieldIndex;
    if (kind == "ARG") return argIndex;
    if (kind == "VAR") return varIndex;
    return 0;
}


std::string SymbolTable::kindOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.kind;
    if (classTableCode != symbolTableClass.end())
        return classTableCode->second.kind;
    return "NONE";
}


std::string SymbolTable::typeOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.type;
    if (classTableCode != symbolTableClass.end())
        return classTableCode->second.type;
    return "NONE";
}


int SymbolTable::indexOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator classTableCode = symbolTableClass.find(name);
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator subroutineTableCode = symbolTableSubroutine.find(name);
    if (subroutineTableCode != symbolTableSubroutine.end())
        return subroutineTableCode->second.index;
    if (classTableCode != symbolTableClass.end())
        return classTableCode->second.index;
    return -1;
}