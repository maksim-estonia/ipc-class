#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "src/IPC/IPC.h"

#include "ipc_common.h"

int main(int argc, char* argv[])
{
    // int c;
    Arguments arg;

    commandLineProcessing(&arg, Direction::WRITE, argc, argv);

    if (!arg.write_path) {
        std::cerr << "ERROR: no file path provided" << std::endl;
        return -1;
    }

    switch (arg.tr_type) {
        case Transport_type::PIPE: {
            std::fstream file;
            std::cout << "Launch Pipe Rx" << std::endl;

            try {
                auto pipe_rx = std::make_unique<CreatorPipeRx>();
                file = pipe_rx->openWriteFile(arg.write_path);

                std::unique_ptr<ReceiverIPC> pipe_file_rx = std::move(pipe_rx->createIpcRx(&file));
                pipe_file_rx->receive();

            } catch (const char* msg) {
                std::cerr << msg << std::endl;
                return -1;
            }

            break;
        }
        case Transport_type::QUEUE:
            std::cerr << "ERROR: not implemented" << std::endl;
            return -1;
        case Transport_type::SHM:
            std::cerr << "ERROR: not implemented" << std::endl;
            return -1;
        default:
            std::cerr << "ERROR: no ipc message type selected" << std::endl;
            return -1;
    }

    return 0;

}