#include <iostream>
#include "IPC.h"

void ShmRx::receive(void) {
    this->setupShmRx();

    this->fileSizeRx();

    this->shmRx();
}

void ShmRx::setupShmRx(void) const {
    ;
}

void ShmRx::fileSizeRx(void) const {
    ;
}

void ShmRx::shmRx() const {
    ;
}