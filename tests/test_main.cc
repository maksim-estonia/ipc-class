#include <gtest/gtest.h>
#include <thread>
#include <iostream>

#include <fstream>
#include <string>
#include "src/IPC/IPC.h"

void run_pipe_rx(void)
{
    std::cout << "run_pipe_rx" << std::endl;

    char path[] = {"data/output.txt"};
    std::fstream file;

    std::cout << "Launch Pipe Rx" << std::endl;
    CreatorIPC* pipe_rx = new CreatorPipeRx();
    file = pipe_rx->openWriteFile(path);
    std::string str1 = "hello";
    file << str1;
    // ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx(&file);
    // std::cout << pipe_file_rx->receive();

    // file.open(path, std::fstream::out | std::fstream::trunc);

    // // check if the file has been opened successfully
    // if (!file.is_open()) {
    //     // the file hasn't been opened; error
    //     std::cerr << "ERROR CreatorIPC: write file couldn't be opened" << std::endl;
    // }
}

void run_pipe_tx(void)
{
    std::cout << "run_pipe_tx" << std::endl;

    char path[] = {"data/input.txt"};
    std::fstream file;

    std::cout << "Launch Pipe Tx" << std::endl;
    CreatorIPC* pipe_tx = new CreatorPipeTx();
    file = pipe_tx->openReadFile(path);
    // SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
    // std::cout << pipe_file_tx->send();
}

int run_pipe_test(void)
{
    std::cout << "----------------------Starting run_pipe_test----------------------" << std::endl;
    std::thread th_rx(run_pipe_rx);
    std::thread th_tx(run_pipe_tx);

    //wait for both threads to finish
    th_rx.join();
    th_tx.join();

    std::cout << "----------------------Ending run_pipe_test----------------------" << std::endl;
    return 0;
}

TEST(IpcTest, Pipe)
{
    run_pipe_test();

    EXPECT_EQ(0, 0);
}

TEST(IpcTest, Queue)
{
    EXPECT_EQ(0, 0);
}

TEST(IpcTest, Shm)
{
    EXPECT_EQ(0, 0);
}

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}