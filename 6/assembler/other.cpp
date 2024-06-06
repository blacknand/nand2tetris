#include <fstream>
#include <map>
#include <string>
#include "other.hpp"


// Overwrites .hack file, appends to file 
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


// Check if string is a decimal
// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool Decimal::is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}