#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include "CompilationEngine.h"
#include "JackTokenizer.h"

int main(int argc, char **argv) {
    

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    CompilationEngine testObj(inputFile, outputFile);
    // std::filesystem::path inputPath(argv[1]);
    // std::vector<std::filesystem::path> jackFiles;

    // if (std::filesystem::is_directory(inputPath)) {
    //     for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(inputPath)) {
    //         if (dirEntry.is_regular_file() && dirEntry.path().extension() == ".jack") {
    //             jackFiles.push_back(dirEntry.path());
    //         }
    //     }
    // } else if (inputPath.extension() == ".jack") 
    //     jackFiles.push_back(inputPath);

    // for (const auto &jackFile: jackFiles) {
    //     std::filesystem::path filePath = jackFile;
    //     std::string outputFileName = filePath.stem().string() + ".xml"; 
    //     testObj.constructor(argv[1], outputFileName);
    // }

    // testObj.constructor(argv[1], argv[1]);
    // JackTokenizer testObj;
    // testObj.initializer(argv[1]);

    // const std::vector<JackTokenizer::Token> &tokens = testObj.getTokens();

    // while (testObj.hasMoreTokens()) {
    //     testObj.advance();
    //     std::string currentTokenType;
    //     switch (testObj.tokenType()) {
    //         case 1:
    //             currentTokenType = "keyword";
    //             break;
    //         case 2:
    //             currentTokenType = "symbol";
    //             break;
    //         case 3:
    //             currentTokenType = "int_const";
    //             break;
    //         case 4:
    //             currentTokenType = "string_const";
    //             break;
    //         case 5:
    //             currentTokenType = "identifier";
    //             break;
    //     }

    //     if (currentTokenType == "keyword") {
    //         switch (testObj.keyWord()) {
    //             case 1:
    //                 // std::cout << "class" << std::endl;
    //                 break;
    //             case 2:
    //                 // std::cout << "method" << std::endl;
    //                 break;
    //             case 3:
    //                 // std::cout << "function" << std::endl;
    //                 break;
    //             case 4:
    //                 // std::cout << "constructor" << std::endl;
    //                 break;
    //             case 5:
    //                 // std::cout << "int" << std::endl;
    //                 break;
    //             case 6:
    //                 // std::cout << "boolean" << std::endl;
    //                 break;
    //             case 7:
    //                 // std::cout << "char" << std::endl;
    //                 break;
    //             case 8:
    //                 // std::cout << "void" << std::endl;
    //                 break;
    //             case 9:
    //                 // std::cout << "var" << std::endl;
    //                 break;
    //             case 10:
    //                 // std::cout << "static" << std::endl;
    //                 break;
    //             case 11:
    //                 // std::cout << "field" << std::endl;
    //                 break;
    //             case 12:
    //                 // std::cout << "let" << std::endl;
    //                 break;
    //             case 13:
    //                 // std::cout << "do" << std::endl;
    //                 break;
    //             case 14:
    //                 // std::cout << "if" << std::endl;
    //                 break;
    //             case 15:
    //                 // std::cout << "else" << std::endl;
    //                 break;
    //             case 16:
    //                 // std::cout << "while" << std::endl;
    //                 break;
    //             case 17:
    //                 // std::cout << "return" << std::endl;
    //                 break;
    //             case 18:
    //                 // std::cout << "true" << std::endl;
    //                 break;
    //             case 19:
    //                 // std::cout << "false" << std::endl;
    //                 break;
    //             case 20:
    //                 // std::cout << "null" << std::endl;
    //                 break;
    //             case 21:
    //                 // std::cout << "this" << std::endl;
    //                 break;
    //         }
    //     }

    //     if (currentTokenType == "symbol") {
    //         // std::cout << testObj.symbol() << std::endl;
    //         ;

    //     }

    //     if (currentTokenType == "identifier") {
    //         // std::cout << testObj.identifier() << std::endl;
    //         ;
    //     }

    //     if (currentTokenType == "int_const") {
    //         // std::cout << testObj.intVal() << std::endl;
    //         ;
    //     }

    //     if (currentTokenType == "string_const") {
    //         std::cout << testObj.stringVal() << std::endl;
            
    //     }

    // }

    return 0;
}