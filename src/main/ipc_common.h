#ifndef IPC_COMMON_H
#define IPC_COMMON_H

#include <getopt.h>
#include <iostream>

/* command line options (for getopt long) */
static struct option long_options[] = 
{
    {"help",        no_argument,        0,  'h'},
    {"queue",       no_argument,        0,  'q'},
    {"pipe",        no_argument,        0,  'p'},
    {"shm",         no_argument,        0,  's'},
    {"file",        required_argument,  0,  'f'},
    {0, 0, 0, 0}
};

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