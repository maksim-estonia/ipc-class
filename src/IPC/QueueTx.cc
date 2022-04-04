#include <iostream>
#include "IPC.h"

void QueueTx::send(void) {
    this->setupQueueTx();

    this->fileSizeTx();

    this->queueTx();
}

void QueueTx::setupQueueTx(void) const {
    ;
}

void QueueTx::fileSizeTx(void) const {
    ;
}

void QueueTx::queueTx(void) const {
    ;
}