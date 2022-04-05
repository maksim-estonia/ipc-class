#ifndef IPC_COMMON_H
#define IPC_COMMON_H

#include <getopt.h>
#include <iostream>

enum class Transport_type
{
    DEFAULT,
    QUEUE,
    PIPE,
    SHM
};

enum class Direction
{
    READ,
    WRITE
};

// structure to store the arguments for a given command
typedef struct
{
    Transport_type  tr_type;
    char            *read_path;
    char            *write_path;
} Arguments;

// function to process command line options
int commandLineProcessing(Arguments *, Direction, int, char * []);

#endif 