#include "IPC.h"

/*
    Concrete Products provide various implementations
    of the Product interface
*/

std::string CreatorIPC::openWriteFile(void) const {
    std::string result = "CreatorIPC: openWriteFile\n";
    return result;
}

std::fstream CreatorIPC::openReadFile(char *path) const {
    // open file (for reading only)
    std::fstream file;
    file.open(path, std::fstream::in);

    // check if the file has been opened successfully
    if (!file.is_open()) {
        // the files hasn't been opened; error
        fprintf(stderr, "read file couldn't be opened\n");
        std::cerr << "ERROR CreatorIPC: read file couldn't be opened" << std::endl;
    }

    std::cout << "CreatorIPC: openReadFile\n";
    return file;
}




