#include "IPC.h"

#include <sys/stat.h>   /* mkfifo() */
#include <fcntl.h>      /* O_CREAT, O_WRONLY */
#include <iostream>     /* std::cout std::ios seekg() */
#include <unistd.h>     /* write() */

#define FIFO "./fifoChannel"

void PipeTx::send(void) {
    this->setupPipeTx();
    
    this->pipeTx();
}

void PipeTx::setupPipeTx(void) {
    mkfifo(FIFO, 0666);                         /* read/write for user/group/others */
    this->fd = open(FIFO, O_CREAT | O_WRONLY);  
    if (fd < 0) {
        throw std::runtime_error("Tx Pipe couldn't be opened");
    }     
}

void PipeTx::pipeTx(void) {
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
        this->readFile->read(this->readBuf, BUFFERSIZE);

        /* if EOF reached, write last part and break loop */
        if (this->readFile->eof()) {
            int remainingBytes = lengthFile - BUFFERSIZE*n;
            /* write to pipe (partial buffer) */
            write(fd, readBuf, remainingBytes);
            this->readBuf[remainingBytes] = '\0';   /* necessary to print out buffer partially */
            #if PRINT
            std::cout << readBuf << std::endl;
            std::cout << "-------------" << std::endl;
            #endif
            break;
        }

        #if PRINT
        std::cout << readBuf << std::endl;
        std::cout << "-------------" << std::endl;
        #endif

        /* write to pipe (full buffer) */
        write(fd, readBuf, BUFFERSIZE);

        n +=1;  /* keeping track of number of full buffer sent */
    }

    /* close readFile */
    this->readFile->close();

    /* close pipe: generates an end-of-stream marker */
    close(fd);
    /* unlink from file */
    unlink(FIFO);
}