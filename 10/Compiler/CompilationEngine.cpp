#include <string>
#include <iostream>
#include <vector>
#include "JackTokenizer.h"

int main(int argc, char **argv) {
    JackTokenizer testObj;
    testObj.initializer(argv[1]);

    const std::vector<JackTokenizer::Token> &tokens = testObj.getTokens();

    while (testObj.hasMoreTokens()) {
        testObj.advance();
        std::string currentTokenType;
        switch (testObj.tokenType()) {
            case 1:
                currentTokenType = "keyword";
                break;
            case 2:
                currentTokenType = "symbol";
                break;
            case 3:
                currentTokenType = "int_const";
                break;
            case 4:
                currentTokenType = "str_const";
                break;
            case 5:
                currentTokenType = "identifier";
                break;
        }

        if (currentTokenType == "keyword") {
            switch (testObj.keyWord()) {
                case 1:
                    std::cout << "class" << std::endl;
                    break;
                case 2:
                    std::cout << "method" << std::endl;
                    break;
                case 3:
                    std::cout << "function" << std::endl;
                    break;
                case 4:
                    std::cout << "constructor" << std::endl;
                    break;
                case 5:
                    std::cout << "int" << std::endl;
                    break;
                case 6:
                    std::cout << "boolean" << std::endl;
                    break;
                case 7:
                    std::cout << "char" << std::endl;
                    break;
                case 8:
                    std::cout << "void" << std::endl;
                    break;
                case 9:
                    std::cout << "var" << std::endl;
                    break;
                case 10:
                    std::cout << "static" << std::endl;
                    break;
                case 11:
                    std::cout << "field" << std::endl;
                    break;
                case 12:
                    std::cout << "let" << std::endl;
                    break;
                case 13:
                    std::cout << "do" << std::endl;
                    break;
                case 14:
                    std::cout << "if" << std::endl;
                    break;
                case 15:
                    std::cout << "else" << std::endl;
                    break;
                case 16:
                    std::cout << "while" << std::endl;
                    break;
                case 17:
                    std::cout << "return" << std::endl;
                    break;
                case 18:
                    std::cout << "true" << std::endl;
                    break;
                case 19:
                    std::cout << "false" << std::endl;
                    break;
                case 20:
                    std::cout << "null" << std::endl;
                    break;
                case 21:
                    std::cout << "this" << std::endl;
                    break;
            }
        }

    }

    return 0;
}