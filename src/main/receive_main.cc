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
    //SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
    //std::cout << pipe_file_tx->send();
}