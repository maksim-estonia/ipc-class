#include <iostream>
#include "IPC.h"

std::string PipeTx::send(void) const {
    std::string result = this->setupPipeTx();
    std::cout << result;

    result = this->fileSizeTx();
    std::cout << result;

    result = this->pipeTx();
    std::cout << result;

    return "PipeTx: send process end\n";
}

std::string PipeTx::setupPipeTx(void) const {
    return "  PipeTx: setupPipeTx\n";
}

std::string PipeTx::fileSizeTx(void) const {
    return "  PipeTx: fileSizeTx\n";
}

std::string PipeTx::pipeTx(void) const {
    return "  PipeTx: pipeTx\n";
}