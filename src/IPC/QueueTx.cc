#include <iostream>
#include "IPC.h"

#include "Queue.h"

#include <sys/stat.h>   /* S_IRWXU S_IRWXG */
#include <sys/ipc.h>    /* IPC_CREAT */
#include <sys/msg.h>    /* msgget() */
#include <string.h>     /* strerror() */

void QueueTx::send(void) {
    this->setupQueueTx();

    this->queueTx();
}

void QueueTx::setupQueueTx(void) {
    key_t key;

    /* ftok - convert a pathname and a project identifier to a System V IPC key */
    key = ftok(PathName, ProjectId);
    if (key < 0) {
        std::cout << "error ftok" << std::endl;
        throw std::runtime_error(strerror(errno));
    }

    /* msgget - get a System V message queue identifier */
    this->qid = msgget(key, S_IRWXU | S_IRWXG | IPC_CREAT);
    if (qid < 0) {
        std::cout << "error msgget" << std::endl;
        throw std::runtime_error(strerror(errno));
    }
}

void QueueTx::queueTx(void) {
    char readBuf[BUFFERSIZE_QUEUE];
    int readBytes = 0;
    int n = 1;  

    while(1) {
        /* reading from readFile */
        readBytes = this->readFile->read(readBuf, BUFFERSIZE_QUEUE).gcount();

        /* if EOF reached, send last part and break loop */
        if (this->readFile->eof()) {
            queuedMessage msg;
            msg.index = (long) n;
            msg.endIndex = (long) n;
            msg.sizeMessage = readBytes;
            strcpy(msg.payload, readBuf);
            /* send the message */
            msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT); /* don't block */
            std::cout << "---------" << std::endl;
            std::cout << "index: " << (int) msg.index << std::endl;
            std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
            std::cout << msg.payload << std::endl;
            std::cout << "---------" << std::endl;
            break;
        }

        /* build the message */
        queuedMessage msg;
        msg.index = (long) n;
        msg.endIndex = (long) (n+1);
        msg.sizeMessage = BUFFERSIZE_QUEUE;
        strcpy(msg.payload, readBuf);
        /* send the message */
        msgsnd(this->qid, &msg, sizeof(msg), IPC_NOWAIT); /* don't block */
        std::cout << "---------" << std::endl;
        std::cout << "index: " << (int) msg.index << std::endl;
        std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
        std::cout << msg.payload << std::endl;
        std::cout << "---------" << std::endl;

        n +=1;
    }
}

QueueTx::~QueueTx(void) {
    /* close readFile */
    this->readFile->close();
}