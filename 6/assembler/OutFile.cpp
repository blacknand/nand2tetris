#include <fstream>
#include <map>
#include <string>
#include "OutFile.hpp"


std::ios_base::openmode OutFile::hasBeenOpened( std::string fileName ) {
    // Test if the key is present
    if (record.find(fileName) == record.end()) {
        record[ fileName ] = true;
        return std::ofstream::trunc;
    } else
        return std::ofstream::app;
}

OutFile::OutFile( const char * filename )
: std::ofstream( filename, hasBeenOpened( std::string( filename ) ) ) {}

std::map< std::string, bool > OutFile::record;