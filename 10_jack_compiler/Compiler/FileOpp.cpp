#include <fstream>
#include <map>
#include <string>
#include "FileOpp.h"

std::map<std::string, bool> WriteToFile::record;

std::ios_base::openmode WriteToFile::hasBeenOpened(std::string fileName) {
    if (record.find(fileName) == record.end()) {
        record[fileName] = true;
        return std::ofstream::trunc;
    } else
        return std::ofstream::app;
}

std::ofstream WriteToFile::fileWriter(const char *fileName) {
    return std::ofstream(fileName, hasBeenOpened(std::string(fileName)));
} 