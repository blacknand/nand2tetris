#include <fstream>
#include <map>
#include <string>
#include "FileOpp.h"

// using regular method
std::ios_base::openmode FileWriting::hasBeenOpened( std::string fileName ) {
    // Test if the key is present
    if (record.find(fileName) == record.end()) {
        record[ fileName ] = true;
        return std::ofstream::trunc;
    } else
        return std::ofstream::app;
}

std::ofstream FileWriting::writeFile( const char * filename ) {
    return std::ofstream(filename, hasBeenOpened(std::string(filename)));
}

std::map< std::string, bool > FileWriting::record;