#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "CodeWriter.h"
#include "FileOp.h"


void CodeWriter::initializer(const char *outputFile) {
    std::ofstream asmFile = fileWriter.writeFile(outputFile);    
}