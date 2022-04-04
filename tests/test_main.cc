#include <gtest/gtest.h>
#include <thread>
#include <iostream>

#include <fstream>
#include <string>
#include "src/IPC/IPC.h"

// file comparison from https://stackoverflow.com/questions/6163611/compare-two-files
#include <iterator>
#include <string>
#include <algorithm>

bool compare_files(const std::string&, const std::string&);

void run_pipe_rx(void)
{
    #if PRINT
    std::cout << "run_pipe_rx" << std::endl;
    #endif

    char path[] = {"data/pipe_output.txt"};
    std::fstream file;

    #if PRINT
    std::cout << "Launch Pipe Rx" << std::endl;
    #endif
    //CreatorIPC* pipe_rx = new CreatorPipeRx();
    auto pipe_rx = std::make_unique<CreatorPipeRx>();
    file = pipe_rx->openWriteFile(path);

    //ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx(&file);
    std::unique_ptr<ReceiverIPC> pipe_file_rx = std::move(pipe_rx->createIpcRx(&file));
    #if PRINT
    std::cout << pipe_file_rx->receive();
    #else
    pipe_file_rx->receive();
    #endif
}

void run_pipe_tx(void)
{
    #if PRINT
    std::cout << "run_pipe_tx" << std::endl;
    #endif

    char path[] = {"data/pipe_input.txt"};
    std::fstream file;

    #if PRINT
    std::cout << "Launch Pipe Tx" << std::endl;
    #endif  
    
    //CreatorIPC* pipe_tx = new CreatorPipeTx();
    auto pipe_tx = std::make_unique<CreatorPipeTx>();
    file = pipe_tx->openReadFile(path);
    
    // SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
    std::unique_ptr<SenderIPC> pipe_file_tx = std::move(pipe_tx->createIpcTx(&file));
    #if PRINT
    std::cout << pipe_file_tx->send();
    #else
    pipe_file_tx->send();
    #endif
}

int run_pipe_test(void)
{
    #if PRINT
    std::cout << "----------------------Starting run_pipe_test----------------------" << std::endl;
    #endif
    std::thread th_rx(run_pipe_rx);
    std::thread th_tx(run_pipe_tx);

    //wait for both threads to finish
    th_rx.join();
    th_tx.join();

    #if PRINT
    std::cout << "----------------------Ending run_pipe_test----------------------" << std::endl;
    #endif
    return 0;
}

TEST(IpcTest, Pipe)
{
    std::string input_path{"data/pipe_input.txt"};
    std::string output_path{"data/pipe_output.txt"};

    // clear output_path file
    std::fstream file_clear;
    file_clear.open(output_path, std::fstream::out | std::fstream::trunc);
    file_clear.close();

    // run pipe file transfer
    run_pipe_test();

    // compare input.txt and output.txt
    bool files_equal = false;
    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

TEST(IpcTest, Queue)
{
    std::string input_path{"data/queue_input.txt"};
    std::string output_path{"data/queue_output.txt"};

    // clear output_path file
    std::fstream file_clear;
    file_clear.open(output_path, std::fstream::out | std::fstream::trunc);
    file_clear.close();

    // run queue file transfer
    //run_queue_test();

    // compare input.txt and output.txt
    bool files_equal = false;
    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

TEST(IpcTest, Shm)
{
    std::string input_path{"data/shm_input.txt"};
    std::string output_path{"data/shm_output.txt"};

    // clear output_path file
    std::fstream file_clear;
    file_clear.open(output_path, std::fstream::out | std::fstream::trunc);
    file_clear.close();

    // run shm file transfer
    //run_shm_test();

    // compare input.txt and output.txt
    bool files_equal = false;
    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

bool compare_files(const std::string& p1, const std::string& p2)
{
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false;   // file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false;   // size mismatch
    }

    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(  std::istreambuf_iterator<char>(f1.rdbuf()),
                        std::istreambuf_iterator<char>(),
                        std::istreambuf_iterator<char>(f2.rdbuf())
                        );
}