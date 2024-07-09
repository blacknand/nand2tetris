#include <string>
#include <iostream>
#include <unordered_map>
#include "SymbolTable.h"


SymbolTable::SymbolTable()
    : staticIndex(0), fieldIndex(0), argIndex(0), varIndex(0) {}


void SymbolTable::reset() {
    symbolTable.clear();
    staticIndex = 0, fieldIndex = 0, argIndex = 0, varIndex = 0;
}


void SymbolTable::define(const std::string &name, const std::string &type, const std::string &kind) {
    if (kind == "static") {
        symbolTable[name] = {type, kind, staticIndex};
        staticIndex++;
    } else if (kind == "field") {
        symbolTable[name] = {type, kind, fieldIndex} ;
        fieldIndex++;
    } else if (kind == "argument") {
        symbolTable[name] = {type, kind, argIndex};
        argIndex++;
    } else if (kind == "var") {
        symbolTable[name] = {type, kind, varIndex};
        varIndex++;
    }
} 


int SymbolTable::varCount(const std::string &kind) const {
    if (kind == "static") return staticIndex;
    if (kind == "field") return fieldIndex;
    if (kind == "argument") return argIndex;
    if (kind == "var") return varIndex;
    return 0;
}


std::string SymbolTable::kindOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator tableCode = symbolTable.find(name);
    if (tableCode != symbolTable.end())
        return tableCode->second.kind;
    return "none";
}


std::string SymbolTable::typeOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator tableCode = symbolTable.find(name);
    if (tableCode != symbolTable.end())
        return tableCode->second.type;
    return "none";
}


int SymbolTable::indexOf(const std::string &name) const {
    std::unordered_map<std::string, SymbolTable::Symbol>::const_iterator tableCode = symbolTable.find(name);
    if (tableCode != symbolTable.end())
        return tableCode->second.index;
    return -1;
}