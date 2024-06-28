#include <fstream>
#include <map>
#include <string>

#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

class FileWriting: public std::ofstream {
    static std::map<std::string, bool> record;
    static std::ios_base::openmode hasBeenOpened(std::string fileName);
    public:
        std::ofstream writeFile(const char *filename);
};

#endif  // WRITE_TO_FILE_HPP