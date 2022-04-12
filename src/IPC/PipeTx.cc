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
    std::cout << "Tx opened" << std::endl;     
}

void PipeTx::pipeTx(void) {
    char readBuf[BUFFERSIZE];
    int n = 0;  /* keeping track of number of full buffer sent */

    /* determine length of file */
    this->readFile->seekg(0, std::ios::beg);    /* set position to begin of file */
    auto begin = this->readFile->tellg();
    this->readFile->seekg(0, std::ios::end);    /* set position to end of file */
    auto end = this->readFile->tellg();
    int lengthFile = (int)(end-begin);          /* store length of file */
    this->readFile->seekg(0, std::ios::beg);    /* set position back to begin */

    #if PRINT
    std::cout << "TOTAL LENGTH: " << lengthFile << std::endl;
    #endif

    while (1) {
        /* reading from readFile */
        this->readFile->read(readBuf, BUFFERSIZE);

        /* if EOF reached, write last part and break loop */
        if (this->readFile->eof()) {
            int remainingBytes = lengthFile - BUFFERSIZE*n;
            /* write to pipe (partial buffer) */
            write(this->fd, readBuf, remainingBytes);
            #if PRINT
            std::cout << std::string(readBuf, remainingBytes) << std::endl;
            std::cout << "-------------" << std::endl;
            #endif
            break;
        }

        #if PRINT
        std::cout << std::string(readBuf, sizeof(readBuf)) << std::endl;
        std::cout << "-------------" << std::endl;
        #endif

        /* write to pipe (full buffer) */
        write(this->fd, readBuf, BUFFERSIZE);

        n +=1;  /* keeping track of number of full buffer sent */
    }
}

PipeTx::~PipeTx(void) {
    this->readFile->close();    /* close readFile */
    close(this->fd);            /* close pipe */
    unlink(FIFO);               /* unlink from the file */
}