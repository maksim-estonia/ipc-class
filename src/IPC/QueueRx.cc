#include <iostream>
#include "IPC.h"

std::string QueueRx::receive(void) {
    std::string result = this->setupQueueRx();
    std::cout << result;

    result = this->fileSizeRx();
    std::cout << result;

    result = this->queueRx();
    std::cout << result;

    return "QueueRx: receive process end\n";
}

std::string QueueRx::setupQueueRx(void) const {
    return "  QueueRx: setupPipeRx\n";
}

std::string QueueRx::fileSizeRx(void) const {
    return "  QueueRx: fileSizeRx\n";
}

std::string QueueRx::queueRx(void) const {
    return "  QueueRx: queueRx\n";
}