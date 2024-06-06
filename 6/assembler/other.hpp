#include <fstream>
#include <map>
#include <string>

#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

class OutFile : public std::ofstream {
    static std::map< std::string, bool > record;

    // Helper function
    static std::ios_base::openmode hasBeenOpened( std::string fileName );
public:
    OutFile( const char * filename );
};

#endif  // WRITE_TO_FILE_HPP


#ifndef IS_NUMBER
#define IS_NUMBER

class Decimal {
    public:
        bool IsNumber(const std::string& s);
};

#endif  // IS_NUMBER