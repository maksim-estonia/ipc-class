#include <iostream>
#include "IPC.h"

std::string ShmTx::send(void) {
    std::string result = this->setupShmTx();
    std::cout << result;

    result = this->fileSizeTx();
    std::cout << result;

    result = this->shmTx();
    std::cout << result;

    return "ShmTx: send process end\n";
}

std::string ShmTx::setupShmTx(void) const {
    return "  ShmTx: setupShmTx\n";
}

std::string ShmTx::fileSizeTx(void) const {
    return "  ShmTx: fileSizeTx\n";
}

std::string ShmTx::shmTx(void) const {
    return "  ShmTx: shmTx\n";
}