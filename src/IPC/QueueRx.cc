#include <iostream>
#include "IPC.h"

void QueueRx::receive(void) {
    this->setupQueueRx();

    this->fileSizeRx();

    this->queueRx();
}

void QueueRx::setupQueueRx(void) const {
    ;
}

void QueueRx::fileSizeRx(void) const {
    ;
}

void QueueRx::queueRx(void) const {
    ;
}