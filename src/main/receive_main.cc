#include <iostream>
#include <fstream>
#include <string>

#include "src/IPC/IPC.h"

int main()
{
    char path[] = {"/home/maksim/ipc-class/output.txt"};
    std::fstream file;

    std::cout << "App: Launch Pipe Rx" << std::endl;
    CreatorIPC* pipe_rx = new CreatorPipeRx();
    file = pipe_rx->openWriteFile(path);
    ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx(&file);
    std::cout << pipe_file_rx->receive();
}