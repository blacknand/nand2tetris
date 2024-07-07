#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

class SymbolTable {
    private:
        struct Symbol {
            std::string type;
            std::string kind;
            int index;
        };
        int staticIndex, fieldIndex, argIndex, varIndex;
        std::unordered_map<std::string, SymbolTable::Symbol> symbolTable;
        // std::unordered_map<std::string, SymbolTable::Symbol> symbolTableSubroutine;
    public:
        SymbolTable();
        void reset();
        void define(const std::string &name, const std::string &type, const std::string &kind);
        int varCount(const std::string &kind) const;
        std::string kindOf(const std::string &name) const;
        std::string typeOf(const std::string &name) const;
        int indexOf(const std::string &name) const;
};

#endif  // SYMBOL_TABLE_H