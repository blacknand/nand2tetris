#include <string>

class SymbolTable {
    public: 
        void initializer();
        void addEntry(std::string symbol, int address);
        bool contains(std::string);
        int getAddress(std::string);
};