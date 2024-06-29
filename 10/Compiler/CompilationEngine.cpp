#include <string>
#include <iostream>
#include <vector>
#include "JackTokenizer.h"

int main(int argc, char **argv) {
    JackTokenizer testObj;
    testObj.initializer(argv[1]);

    const std::vector<std::vector<std::string>> &tokenizedVec = testObj.getTokenizedVec();

    for (int i = 0; i < tokenizedVec.size(); i++) {
        for (int j = 0; j < tokenizedVec[i].size(); j++) {
            std::cout << tokenizedVec[i][j] << std::endl;
        }
    }

    std::cout << "compiles" << std::endl;
    return 0;
}