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

#define PRINT_PIPE 0

bool compare_files(const std::string&, const std::string&);

void run_pipe_rx(void)
{
    #if PRINT_PIPE
    std::cout << "run_pipe_rx" << std::endl;
    #endif

    char path[] = {"data/pipe_output.txt"};
    std::fstream file;

    #if PRINT_PIPE
    std::cout << "Launch Pipe Rx" << std::endl;
    #endif
    CreatorIPC* pipe_rx = new CreatorPipeRx();
    file = pipe_rx->openWriteFile(path);

    ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx(&file);
    std::cout << pipe_file_rx->receive();
}

void run_pipe_tx(void)
{
    #if PRINT_PIPE
    std::cout << "run_pipe_tx" << std::endl;
    #endif

    char path[] = {"data/pipe_input.txt"};
    std::fstream file;

    #if PRINT_PIPE
    std::cout << "Launch Pipe Tx" << std::endl;
    #endif  
    CreatorIPC* pipe_tx = new CreatorPipeTx();
    file = pipe_tx->openReadFile(path);

    SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
    std::cout << pipe_file_tx->send();
}

int run_pipe_test(void)
{
    #if PRINT_PIPE
    std::cout << "----------------------Starting run_pipe_test----------------------" << std::endl;
    #endif
    std::thread th_rx(run_pipe_rx);
    std::thread th_tx(run_pipe_tx);

    //wait for both threads to finish
    th_rx.join();
    th_tx.join();

    #if PRINT_PIPE
    std::cout << "----------------------Ending run_pipe_test----------------------" << std::endl;
    #endif
    return 0;
}

TEST(IpcTest, Pipe)
{
    // run pipe file transfer
    run_pipe_test();

    // compare input.txt and output.txt
    std::string input_path{"data/pipe_input.txt"};
    std::string output_path{"data/pipe_output.txt"};
    bool files_equal;

    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

TEST(IpcTest, Queue)
{
    // run queue file transfer
    //run_queue_test();

    // compare input.txt and output.txt
    std::string input_path{"data/input.txt"};
    std::string output_path{"data/output.txt"};
    bool files_equal;

    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

TEST(IpcTest, Shm)
{
    // run shm file transfer
    //run_shm_test();

    // compare input.txt and output.txt
    std::string input_path{"data/input.txt"};
    std::string output_path{"data/output.txt"};
    bool files_equal;

    files_equal = compare_files(input_path, output_path);

    EXPECT_TRUE(files_equal);
}

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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