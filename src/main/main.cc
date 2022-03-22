#include <iostream>
#include <string>

#include "src/IPC/IPC.h"

int main()
{

    std::cout << "App: Launch Pipe Rx" << std::endl;
    CreatorIPC* pipe_rx = new CreatorPipeRx();
    std::cout << pipe_rx->openWriteFile();
    ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx();
    std::cout << pipe_file_rx->receive();
    std::cout << std::endl;
    
    std::cout << "App: Launch Queue Rx" << std::endl;
    CreatorIPC* queue_rx = new CreatorQueueRx();
    std::cout << queue_rx->openWriteFile();
    ReceiverIPC* queue_file_rx = queue_rx->createIpcRx();
    std::cout << queue_file_rx->receive();
    std::cout << std::endl;

    std::cout << "App: Launch Shm Rx" << std::endl;
    CreatorIPC* shm_rx = new CreatorShmRx();
    std::cout << shm_rx->openWriteFile();
    ReceiverIPC* shm_file_rx = shm_rx->createIpcRx();
    std::cout << shm_file_rx->receive();
    std::cout << std::endl;

    std::cout << "App: Launch Pipe Tx" << std::endl;
    CreatorIPC* pipe_tx = new CreatorPipeTx();
    std::cout << pipe_tx->openReadFile();
    SenderIPC* pipe_file_tx = pipe_tx->createIpcTx();
    std::cout << pipe_file_tx->send();
    std::cout << std::endl;

    std::cout << "App: Launch Queue Tx" << std::endl;
    CreatorIPC* queue_tx = new CreatorQueueTx();
    std::cout << queue_tx->openReadFile();
    SenderIPC* queue_file_tx = queue_tx->createIpcTx();
    std::cout << queue_file_tx->send();
    std::cout << std::endl;

    std::cout << "App: Launch Shm Tx" << std::endl;
    CreatorIPC* shm_tx = new CreatorShmTx();
    std::cout << shm_tx->openReadFile();
    SenderIPC* shm_file_tx = shm_tx->createIpcTx();
    std::cout << shm_file_tx->send();
    std::cout << std::endl; 

    delete pipe_rx;
    delete queue_rx;
    delete shm_rx;
    delete pipe_tx;
    delete queue_tx;
    delete shm_tx;

    delete pipe_file_rx;
    delete queue_file_rx;
    delete shm_file_rx;
    delete pipe_file_tx;
    delete queue_file_tx;
    delete shm_file_tx;


    return EXIT_SUCCESS;
}