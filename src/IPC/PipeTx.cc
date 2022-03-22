#include <iostream>
#include "IPC.h"

std::string PipeTx::send(void) {
    std::string result = this->setupPipeTx();
    std::cout << result;

    result = this->fileSizeTx();
    std::cout << result;

    result = this->pipeTx();
    std::cout << result;

    // close pipe
    close(this->fd);
    //close file
    this->file->close();

    return "PipeTx: send process end\n";
}

std::string PipeTx::setupPipeTx(void) {
    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
    return "  PipeTx: setupPipeTx\n";
}

std::string PipeTx::fileSizeTx(void) {
    // find file size
    // set position to begin of file
    this->file->seekg(0, std::ios::beg);
    auto begin = this->file->tellg();
    // set position to end of file
    this->file->seekg(0, std::ios::end);
    auto end = this->file->tellg();
    this->size = (int)(end-begin);
    // set position back to begin
    this->file->seekg(0, std::ios::beg);

    std::cout << "  FILE SIZE: " << this->size << std::endl;

    // send file size
    sprintf(this->readbuf, "%d", this->size);
    write(this->fd, this->readbuf, strlen(this->readbuf));
    usleep(100000); // 100ms

    return "  PipeTx: fileSizeTx\n";
}

std::string PipeTx::pipeTx(void) {
    int n = 0;
    while (1) {
        this->file->read(this->readbuf, sizeof(this->readbuf)-1);

        if (this->file->eof()){
            // EOF reached, send last string
            int remaining_bytes = (this->size) - (sizeof(readbuf)-1)*n;
            readbuf[remaining_bytes] = '\0';
            std::cout << "Last string: " << readbuf << std::endl;
            write(this->fd, this->readbuf, remaining_bytes);
            usleep(100000); // 100ms
            break;
        }

        // sending full buffer
        this->readbuf[sizeof(this->readbuf)-1] = '\0';
        std::cout << "Read string: " << this->readbuf << std::endl;
        write(this->fd, this->readbuf, sizeof(this->readbuf));
        usleep(100000); // 100ms
        n +=1;
    }

    return "  PipeTx: pipeTx\n";
}