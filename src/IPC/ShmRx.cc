#include <iostream>
#include "IPC.h"

std::string ShmRx::receive(void) {
    std::string result = this->setupShmRx();
    std::cout << result;

    result = this->fileSizeRx();
    std::cout << result;

    result = this->shmRx();
    std::cout << result;

    return "ShmRx: receive process end\n";
}

std::string ShmRx::setupShmRx(void) const {
    return "  ShmRx: setupShmRx\n";
}

std::string ShmRx::fileSizeRx(void) const {
    return "  ShmRx: fileSizeRx\n";
}

std::string ShmRx::shmRx() const {
    return "  ShmRx: shmRx\n";
}