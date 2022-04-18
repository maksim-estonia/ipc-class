#include <iostream>
#include "IPC.h"

#include "Queue.h"

#include <sys/stat.h>   /* S_IRWXU S_IRWXG */
#include <sys/ipc.h>    /* IPC_CREAT */
#include <sys/msg.h>    /* msgget() */
#include <string.h>     /* strerror() */

char readBuf[BUFFERSIZE];

void QueueTx::send(void) {
    this->setupQueueTx();

    this->queueTx();
}

void QueueTx::setupQueueTx(void) {
    key_t key;

    /* ftok - convert a pathname and a project identifier to a System V IPC key */
    key = ftok(PathName, ProjectId);
    if (key < 0) {
        throw std::runtime_error(strerror(errno));
    }

    /* msgget - get a System V message queue identifier */
    this->qid = msgget(key, S_IRWXU | S_IRWXG | IPC_CREAT);
    if (qid < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void QueueTx::queueTx(void) {
    // char readBuf[BUFFERSIZE_QUEUE];
    int readBytes = 0;
    long n = 1; 
    int status = 0; 

    while(1) {
        /* reading from readFile */
        readBytes = this->readFile->read(readBuf, BUFFERSIZE).gcount();
        if ( (this->readFile->rdstate() & std::ifstream::badbit) != 0 ) {
            throw std::runtime_error("istream::read error");
        }

        /* if EOF reached, send last part and break loop */
        if (this->readFile->eof()) {
            /* build the message */
            queuedMessage msg;
            msg.index = n;
            msg.endIndex = n;
            msg.sizeMessage = readBytes;
            strcpy(msg.payload, readBuf);
            /* send the message */
            status = msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT); /* don't block */
            if (status < 0) {
                throw std::runtime_error(strerror(errno));
            }
            #if PRINT
            std::cout << "---------" << std::endl;
            std::cout << "index: " << n << std::endl;
            std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
            std::cout << std::string(msg.payload, msg.sizeMessage) << std::endl;
            std::cout << "---------" << std::endl;
            #endif
            break;
        }

        /* build the message */
        queuedMessage msg;
        msg.index = n;
        msg.endIndex = (n+1);
        msg.sizeMessage = BUFFERSIZE;
        strcpy(msg.payload, readBuf);
        /* send the message */
        status = msgsnd(this->qid, &msg, sizeof(msg), IPC_NOWAIT); /* don't block */
        if (status < 0) {
            throw std::runtime_error(strerror(errno));
        }
        #if PRINT
        std::cout << "---------" << std::endl;
        std::cout << "index: " << n << std::endl;
        std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
        std::cout << std::string(msg.payload, msg.sizeMessage) << std::endl;
        std::cout << "---------" << std::endl;
        #endif

        n +=1;
    }
}

QueueTx::~QueueTx(void) {
    /* close readFile */
    this->readFile->close();
}