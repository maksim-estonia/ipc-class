#include <iostream>
#include "IPC.h"

std::string PipeRx::receive(void) const {
    std::string result = this->setupPipeRx();
    std::cout << result;

    result = this->fileSizeRx();
    std::cout << result;

    result = this->pipeRx();
    std::cout << result;

    return "PipeRx: receive process end\n";
}

std::string PipeRx::setupPipeRx(void) const {
    return "  PipeRx: setupPipeRx\n";
}

std::string PipeRx::fileSizeRx(void) const {
    return "  PipeRx: fileSizeRx\n";
}

std::string PipeRx::pipeRx(void) const {
    return "  PipeRx: pipeRx\n";
}