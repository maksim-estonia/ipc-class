#include "IPC.h"

/*
    Concrete Products provide various implementations
    of the Product interface
*/

std::fstream CreatorIPC::openWriteFile(const char *path) const {
    // open file (for writing only)
    std::fstream file;
    file.open(path, std::fstream::out | std::fstream::trunc);

    // check if the file has been opened successfully
    if (!file.is_open()) {
        // the file hasn't been opened; error
        std::cerr << "ERROR CreatorIPC: write file couldn't be opened" << std::endl;
    }

    #if PRINT
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
    return file;
}

std::fstream CreatorIPC::openReadFile(const char *path) const {
    // open file (for reading only)
    std::fstream file;
    file.open(path, std::fstream::in);

    // check if the file has been opened successfully
    if (!file.is_open()) {
        // the files hasn't been opened; error
        std::cerr << "ERROR CreatorIPC: read file couldn't be opened" << std::endl;
    }

    #if PRINT
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
    return file;
}




