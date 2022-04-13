#include "IPC.h"

#include <sys/stat.h>   /* mkfifo() */
#include <fcntl.h>      /* O_CREAT, O_WRONLY */
#include <iostream>     /* std::cout std::ios seekg() */
#include <unistd.h>     /* write() */
#include <errno.h>      /* errno */
#include <string.h>     /* strerror */

#define FIFO "./fifoChannel"

void PipeTx::send(void) {
    this->setupPipeTx();
    
    this->pipeTx();
}

void PipeTx::setupPipeTx(void) {
    int status = mkfifo(FIFO, S_IRWXU | S_IRWXG);
    if (status < 0) {
        if (errno == EEXIST) {
            ;   /* if fifo file already exists this is ok */
        }
        else {
            throw std::runtime_error(strerror(errno));
        }
    }
    this->fd = open(FIFO, O_WRONLY);  
    if (this->fd < 0) {
        throw std::runtime_error("Tx Pipe couldn't be opened");
    }
    #if PRINT
    std::cout << "Tx opened" << std::endl;
    #endif     
}

void PipeTx::pipeTx(void) {
    char readBuf[BUFFERSIZE];
    int n = 0;  /* keeping track of number of full buffer sent */
    int readBytes = 0;
    int writeBytes = 0;

    while (1) {
        /* reading from readFile */
        readBytes = this->readFile->read(readBuf, BUFFERSIZE).gcount();

        /* if EOF reached, write last part and break loop */
        if (this->readFile->eof()) {
            /* write to pipe (partial buffer) */
            writeBytes = write(this->fd, readBuf, readBytes);
            if (writeBytes < 0) {
                throw std::runtime_error(strerror(errno));
            }
            #if PRINT
            std::cout << std::string(readBuf, readBytes) << std::endl;
            std::cout << "-------------" << std::endl;
            #endif
            break;
        }

        #if PRINT
        std::cout << std::string(readBuf, sizeof(readBuf)) << std::endl;
        std::cout << "-------------" << std::endl;
        #endif

        /* write to pipe (full buffer) */
        writeBytes = write(this->fd, readBuf, readBytes);
        if (writeBytes < 0) {
            throw std::runtime_error(strerror(errno));
        }

        n +=1;  /* keeping track of number of full buffer sent */
    }
}

PipeTx::~PipeTx(void) {
    this->readFile->close();    /* close readFile */
    close(this->fd);            /* close pipe */
    unlink(FIFO);               /* unlink from the file */
}