#include "IPC.h"

/*
    Concrete Products provide various implementations
    of the Product interface
*/

std::string CreatorIPC::SomeOperation(void) const {
    // Call the factory method to create a Product object.
    ReceiverIPC* file_transport = this->createIpcRx();
    // Now, use the product.
    std::string result = "CreatorIPC: The same creator's code has just worked with " + file_transport->receive();
    delete file_transport;
    return result;
}

std::string CreatorIPC::openWriteFile(void) const {
    std::string result = "CreatorIPC: openWriteFile\n";
    return result;
}

std::string CreatorIPC::openReadFile(char *path) const {
    // open file (for reading only)
    std::fstream file;
    file.open(path, std::fstream::in);

    // check if the file has been opened successfully
    if (!file.is_open()) {
        // the files hasn't been opened; error
        fprintf(stderr, "read file couldn't be opened\n");
    }

    std::string result = "CreatorIPC: openReadFile\n";
    return result;
}




