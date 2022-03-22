#include <iostream>
#include <string>

#include "src/IPC/IPC.h"

int main()
{
    std::cout << "App: Launch Pipe Tx" << std::endl;
    CreatorIPC* pipe_tx = new CreatorPipeTx();
    std::cout << pipe_tx->openReadFile();
    SenderIPC* pipe_file_tx = pipe_tx->createIpcTx();
    std::cout << pipe_file_tx->send();
    std::cout << std::endl;
}