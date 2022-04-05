#include <iostream>
#include "IPC.h"

void PipeRx::receive(void) {
    this->setupPipeRx();

    this->fileSizeRx();

    this->pipeRx();

    // close pipe
    close(fd);
    // close the file
    file->close();

    #if PRINT
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
}

void PipeRx::setupPipeRx(void) {
    // create a FIFO/named pipe
    mknod(FIFO_FILE, S_IFIFO|0640, 0);

    // open pipe
    fd = open(FIFO_FILE, O_RDONLY);

    if (fd == -1) {
        throw std::runtime_error("Pipe-Rx couldn't be opened");
    }

    #if PRINT
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
}

void PipeRx::fileSizeRx(void) {
    // read data, first data is the length of the text file
    while (size == 0) {
        read_bytes = read(fd, readbuf, PIPE_SIZE);
        size = atoi(readbuf);
    }

    #if PRINT
    std::cout << "FILE SIZE: " << size << std::endl;
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
}

void PipeRx::pipeRx(void) {
    int total_read_bytes = 0;
    
    while (1) {
        read_bytes = read(fd, readbuf, PIPE_SIZE-1);
        if (read_bytes == -1) {
            throw std::runtime_error("Pipe-Rx read failed");
        }
        // if (read_bytes <= 1) {
            //skip empty read
            // continue;
        // }
        total_read_bytes += read_bytes;
        readbuf[read_bytes] = '\0';

        #if PRINT
        std::cout << "Received string: " << readbuf << std::endl;
        std::cout << "--->" << (int)strlen(readbuf) << std::endl;
        #endif

        // write to file
        *file << readbuf;


        // if all bytes received, we can stop
        if (total_read_bytes >= size) {
            break;
        }
    }

    #if PRINT
    std::cout << __PRETTY_FUNCTION__ << " finished" << std::endl;
    #endif
}