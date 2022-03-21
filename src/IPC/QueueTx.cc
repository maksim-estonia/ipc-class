#include <iostream>
#include "IPC.h"

std::string QueueTx::send(void) const {
    std::string result = this->setupQueueTx();
    std::cout << result;

    result = this->fileSizeTx();
    std::cout << result;

    result = this->queueTx();
    std::cout << result;

    return "QueueTx: send process end\n";
}

std::string QueueTx::setupQueueTx(void) const {
    return "  QueueTx: setupQueueTx\n";
}

std::string QueueTx::fileSizeTx(void) const {
    return "  PipeTx: fileSizeTx\n";
}

std::string QueueTx::queueTx(void) const {
    return "  QueueTx: queueTx\n";
}