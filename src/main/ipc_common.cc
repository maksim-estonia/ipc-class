#include "ipc_common.h"

int commandLineProcessing(Arguments *arg, Direction dir, int argc, char * argv[]) {
    int c;

    /* Default arguments values */
    arg->tr_type = Transport_type::DEFAULT;
    arg->read_path = NULL;
    arg->write_path = NULL;

    /* if not enough arguments given */
    if (argc < 2) {
        std::cerr << "ERROR: requires arguments \n" << std::endl;
        return -1;
    }

    while (1) {
        int option_index = 0;

        c = getopt_long(argc, argv, "hqpsf:", long_options, &option_index);

        /* detect the end of options */
        if (c == -1)
            break;
        
        switch (c) {
            case 'q':
                arg->tr_type = Transport_type::QUEUE;
                break;
            case 'p':
                arg->tr_type = Transport_type::PIPE;
                break;
            case 's':
                arg->tr_type = Transport_type::SHM;
                break;
            case 'f':
                switch (dir)
                {
                case Direction::READ:
                    arg->read_path = optarg;
                    break;
                case Direction::WRITE:
                    arg->write_path = optarg;
                    break;
                default:
                    break;
                }
                break;
            case 'h':
                std::cout << "\n Use the program as follows: \n" << std::endl;
                std::cout << "--help: prints out a help text containing short description of all supported command-line arguments \n" << std::endl;
                std::cout << "--queue <TBD>: use message queue as IPC method \n" << std::endl;
                std::cout << "--pipe <TBD>: use pipe as IPC method \n" << std::endl;
                std::cout << "--shm: use shared memory buffer as IPC method \n" << std::endl;
                std::cout << "--file [filename]: file used to read/write data from/to \n" << std::endl;
                return -1;
            
            default:
                std::cerr << "ERROR: unknown arguments provided" << std::endl;
                return -1;
        }
    }
    return 0;
}