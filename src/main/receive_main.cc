#include <iostream>
#include <fstream>
#include <string>

#include "src/IPC/IPC.h"

#include "ipc_common.h"

int main(int argc, char* argv[])
{
    // int c;
    Arguments arg;

    commandLineProcessing(&arg, WRITE, argc, argv);

    if (!arg.write_path) {
        std::cerr << "ERROR: no file path provided" << std::endl;
        return -1;
    }

    switch (arg.tr_type) {
        case PIPE: {
            std::fstream file;
            std::cout << "Launch Pipe Rx" << std::endl;
            CreatorIPC* pipe_rx = new CreatorPipeRx();
            file = pipe_rx->openWriteFile(arg.write_path);
            ReceiverIPC* pipe_file_rx = pipe_rx->createIpcRx(&file);
            std::cout << pipe_file_rx->receive();
            break;
        }
        case QUEUE:
            std::cerr << "ERROR: not implemented" << std::endl;
            break;
        case SHM:
            std::cerr << "ERROR: not implemented" << std::endl;
            break;
        default:
            std::cerr << "ERROR: no ipc message type selected" << std::endl;
            return -1;
    }

    return 0;

}