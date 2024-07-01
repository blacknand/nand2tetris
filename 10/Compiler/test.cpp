#include "FileOpp.h"

int main(int argc, char **argv) {
    WriteToFile fileObj;
    fileObj.fileWriter(argv[1]);
}