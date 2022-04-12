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
    std::cout << "Rx opened" << std::endl;
}

void PipeRx::pipeRx(void) {
    ssize_t count;

    while (1) {
        count = read(this->fd, writeBuf, BUFFERSIZE);

        /* end-of-stream */
        if (count == 0)
            break;
        
        else {
            #if PRINT
            // if (count < BUFFERSIZE) {
            //     this->writeBuf[count] = '\0';  /* necessary to print out buffer partially */
            // }
            std::cout << std::string(writeBuf, count) << std::endl;
            std::cout << "-------------" << std::endl;
            #endif
            /* write to writeFile */
            this->writeFile->write(writeBuf, count);
        }
    }

    close(this->fd);    /* close pipe from read end */
    unlink(FIFO);       /* unlink from the file */
}