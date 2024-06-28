#include <fstream>
#include <map>
#include <string>

#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

// https://stackoverflow.com/questions/40873849/append-data-to-a-file-in-c-but-overwrite-if-the-program-is-re-executed
class WriteToFile: public std::ofstream {
    static std::map<std::string, bool> record;
    static std::ios_base::openmode hasBeenOpened(std::string fileName);
public:
    WriteToFile(const char *fileName);
}

#endif  // WRITE_TO_FILE_HPP