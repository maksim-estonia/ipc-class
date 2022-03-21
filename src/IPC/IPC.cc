#include "IPC.h"

std::string print_test(void) {
    std::cout << "Import successfull! \n";

    return "Success";
}

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

std::string CreatorIPC::openReadFile(void) const {
    std::string result = "CreatorIPC: openReadFile\n";
    return result;
}




