#include <string>
#include <iostream>
#include <vector>
#include "JackTokenizer.h"

int main(int argc, char **argv) {
    JackTokenizer testObj;
    testObj.initializer(argv[1]);

    const std::vector<JackTokenizer::Token>& tokens = testObj.getTokens();

    while (testObj.hasMoreTokens()) {
        std::cout << "hasMoreTokens: true" << std::endl;
        testObj.advance();
    }

    return 0;
}