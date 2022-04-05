#include <iostream>
#include "IPC.h"

void ShmTx::send(void) {
    this->setupShmTx();

    this->fileSizeTx();

    this->shmTx();
}

void ShmTx::setupShmTx(void) const {
    ;
}

void ShmTx::fileSizeTx(void) const {
    ;
}

void ShmTx::shmTx(void) const {
    ;
}