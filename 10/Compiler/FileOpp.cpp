#include <fstream>
#include <map>
#include <string>
#include "FileOpp.h"

std::map<std::string, bool> WriteToFile::record;

WriteToFile::hasBeenOpened(std::string fileName) {
    if (record.find(fileName) == record.end()) {
        record[fileName] = true;
        return std::ofstream::trunc;
    } else
        return std::ofstream::app;
}

WriteToFile::WriteToFile(const char *fileName) : std::ofstream(fileName, hasBeenOpened(std::string(fileName))) {}