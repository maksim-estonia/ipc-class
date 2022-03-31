#include <iostream>
#include <fstream>
#include <string>

#include "src/IPC/IPC.h"

#include "ipc_common.h"

int main(int argc, char* argv[])
{
    //int c;
    Arguments arg;

    commandLineProcessing(&arg, READ, argc, argv);

    if (!arg.read_path) {
        std::cerr << "ERROR: no file path provided" << std::endl;
        return -1;
    }

    switch (arg.tr_type) {
        case PIPE: {
            std::fstream file;
            std::cout << "Launch Pipe Tx" << std::endl;
            CreatorIPC* pipe_tx = new CreatorPipeTx();
            file = pipe_tx->openReadFile(arg.read_path);
            SenderIPC* pipe_file_tx = pipe_tx->createIpcTx(&file);
            std::cout << pipe_file_tx->send();
            break;
        }
        case QUEUE: {
            std::cerr << "ERROR: not implemented" << std::endl;
            break;
        }
        case SHM: {
            std::cerr << "ERROR: not implemented" << std::endl;
            break;
        }
        default:
            std::cerr << "ERROR: no ipc message type selected" << std::endl;
            return -1;
    }

    return 0;

}