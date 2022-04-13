#include "IPC.h"

#include <iostream>
#include <fcntl.h>      /* O_RDONLY */
#include <unistd.h>     /* read() close() unlink() */
#include <sys/stat.h>   /* mkfifo() */
#include <errno.h>  
#include <string.h>

#define FIFO "./fifoChannel"

void PipeRx::receive(void) {
    this->setupPipeRx();

    this->pipeRx();
}

void PipeRx::setupPipeRx(void) {
    int status = mkfifo(FIFO, S_IRWXU | S_IRWXG);
    if (status < 0) {
        if (errno == EEXIST) {
            ;   /* if fifo file already exists this is ok */
        }
        else {
            throw std::runtime_error(strerror(errno));
        }
    }
    this->fd = open(FIFO, O_RDONLY);
    if (this->fd < 0) {
        throw std::runtime_error(strerror(errno));
    }
    #if PRINT
    std::cout << "Rx opened" << std::endl;
    #endif
}

void PipeRx::pipeRx(void) {
    char writeBuf[BUFFERSIZE];
    ssize_t count;

    while (1) {
        count = read(this->fd, writeBuf, BUFFERSIZE);

        /* end-of-stream */
        if (count == 0)
            break;
        
        else {
            #if PRINT
            std::cout << std::string(writeBuf, count) << std::endl;
            std::cout << "-------------" << std::endl;
            #endif
            /* write to writeFile */
            this->writeFile->write(writeBuf, count);
        }
    }
}

PipeRx::~PipeRx(void) {
    this->writeFile->close();   /* close writeFile */
    close(this->fd);            /* close pipe */
    unlink(FIFO);               /* unlink from the file */
}