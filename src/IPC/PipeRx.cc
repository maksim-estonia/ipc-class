#include <iostream>
#include "IPC.h"

#define PRINT 0

std::string PipeRx::receive(void) {
    std::string result = this->setupPipeRx();
    #if PRINT
    std::cout << result;
    #endif

    result = this->fileSizeRx();
    #if PRINT
    std::cout << result;
    #endif

    result = this->pipeRx();
    #if PRINT
    std::cout << result;
    #endif

    // close pipe
    close(fd);
    // close the file
    file->close();

    return "PipeRx: receive process end\n";
}

std::string PipeRx::setupPipeRx(void) {
    // create a FIFO/named pipe
    mknod(FIFO_FILE, S_IFIFO|0640, 0);

    // open pipe
    fd = open(FIFO_FILE, O_RDONLY);

    return "  PipeRx: setupPipeRx\n";
}

std::string PipeRx::fileSizeRx(void) {
    // read data, first data is the length of the text file
    while (size == 0) {
        read_bytes = read(fd, readbuf, PIPE_SIZE);
        size = atoi(readbuf);
    }
    #if PRINT
    std::cout << "FILE SIZE: " << size << std::endl;
    #endif

    return "  PipeRx: fileSizeRx\n";
}

std::string PipeRx::pipeRx(void) {
    int total_read_bytes = 0;
    
    while (1) {
        read_bytes = read(fd, readbuf, PIPE_SIZE-1);
        if (read_bytes <= 1) {
            // skip empty read
            continue;
        }
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

    return "  PipeRx: pipeRx\n";
}