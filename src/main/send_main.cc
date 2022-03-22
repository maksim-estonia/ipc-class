#include <iostream>
#include <fstream>
#include <string>

#include "src/IPC/IPC.h"

int main()
{
    char path[] = {"/home/maksim/ipc-class/input.txt"};
    std::fstream file;

    std::cout << "App: Launch Pipe Tx" << std::endl;
    CreatorIPC* pipe_tx = new CreatorPipeTx();
    file = pipe_tx->openReadFile(path);
    SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
    std::cout << pipe_file_tx->send();
}