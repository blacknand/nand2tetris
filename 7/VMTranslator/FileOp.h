#include <fstream>
#include <map>
#include <string>

#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

class OutFile : public std::ofstream {
    static std::map< std::string, bool > record;

    // https://stackoverflow.com/questions/40873849/append-data-to-a-file-in-c-but-overwrite-if-the-program-is-re-executed
    static std::ios_base::openmode hasBeenOpened( std::string fileName );
public:
    OutFile( const char * filename );
};

#endif  // WRITE_TO_FILE_HPP