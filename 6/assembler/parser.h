#include <string>

class Parser {
    public:
        void initializer(std::string file);
        bool hasMoreLines();
        void advance();
        const std::string instructionType();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
};
