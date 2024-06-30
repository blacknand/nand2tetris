#include <string>
#include <iostream>
#include <vector>
#include "JackTokenizer.h"

int main(int argc, char **argv) {
    JackTokenizer testObj;
    testObj.initializer(argv[1]);

    // const std::vector<JackTokenizer::Token>& tokens = testObj.getTokens();

    while (testObj.hasMoreTokens()) {
        testObj.advance();
        // std::cout << testObj.tokenType() << std::endl;
        switch (testObj.tokenType()) {
            case 1:
                std::cout << "KEYWORD" << std::endl;
                break;
            case 2:
                std::cout << "SYMBOL" << std::endl;
                break;
            case 3:
                std::cout << "INT_CONST" << std::endl;
                break;
            case 4:
                std::cout << "STR_CONST" << std::endl;
                break;
            case 5:
                std::cout << "IDENTIFIER" << std::endl;
                break;
        }
    }

    return 0;
}