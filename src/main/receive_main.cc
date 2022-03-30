#include <iostream>
#include <fstream>
#include <string>

#include "src/IPC/IPC.h"

#include "ipc_common.h"

int main(int argc, char* argv[])
{
    int c;
    Arguments arg;

    /* Default arguments values */
    arg.tr_type = DEFAULT;
    arg.read_path = NULL;
    arg.write_path = NULL;

    /* if not enough arguments given */
    if (argc < 2) {
        std::cerr << "ERROR: receive_main requires arguments \n" << std::endl;
        return -1;
    }

    while (1)
    {
        int option_index = 0;

        c = getopt_long(argc, argv, "hqpsf:", long_options, &option_index);

        /* detect the end of options */
        if (c == -1)
            break;
        
        switch (c) {
            case 'q':
                arg.tr_type = QUEUE;
                break;
            case 'p':
                arg.tr_type = PIPE;
                break;
            case 's':
                arg.tr_type = SHM;
                break;
            case 'f':
                arg.write_path = optarg;
                break;
            
            case 'h':
                std::cout << "\n Use the program as follows: \n" << std::endl;
                std::cout << "--help: prints out a help text containing short description of all supported command-line arguments \n" << std::endl;
                std::cout << "--queue: use message queue as IPC method \n" << std::endl;
                std::cout << "--pipe: use pipe as IPC method \n" << std::endl;
                std::cout << "--shm: use shared memory buffer as IPC method \n" << std::endl;
                std::cout << "--file [filename]: file used to write data to \n" << std::endl;
                return -1;
            
            default:
                std::cerr << "ERROR: unknown arguments provided" << std::endl;
                return -1;
        }
    }

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