#include <fstream>
#include <map>
#include <string>
#include "FileOp.h"

// https://stackoverflow.com/questions/40873849/append-data-to-a-file-in-c-but-overwrite-if-the-program-is-re-executed
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