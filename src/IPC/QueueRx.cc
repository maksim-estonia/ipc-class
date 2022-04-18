#include <iostream>
#include "IPC.h"

#include "Queue.h"

#include <sys/stat.h>   /* S_IRWXU S_IRWXG */
#include <sys/ipc.h>    /* IPC_CREAT */
#include <sys/msg.h>    /* msgget() */
#include <string.h>     /* strerror() */

char writeBuf[BUFFERSIZE];
queuedMessage msg;

void QueueRx::receive(void) {
    this->setupQueueRx();

    this->queueRx();
}

void QueueRx::setupQueueRx(void) {
    key_t key;

    /* setup message queue */
    key = ftok(PathName, ProjectId);    /* key to identify the queue */
    if (key<0) {
        throw std::runtime_error(strerror(errno));
    }

    this->qid = msgget(key, S_IRWXU | S_IRWXG | IPC_CREAT);
    if (this->qid < 0) {
        throw std::runtime_error(strerror(errno));
    }

}

void QueueRx::queueRx(void) {
    long n = 1;

    while (1) {

        if (msgrcv(this->qid, &msg, sizeof(msg), n, MSG_NOERROR | IPC_NOWAIT) < 0) {
            throw std::runtime_error(strerror(errno));
        }

        strcpy(writeBuf, msg.payload);
        #if PRINT
        std::cout << "---------" << std::endl;
        std::cout << "index: " << n << std::endl;
        std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
        std::cout << std::string(msg.payload, msg.sizeMessage) << std::endl;
        std::cout << "endIndex: " << msg.endIndex << std::endl;
        std::cout << "---------" << std::endl;
        #endif
        this->writeFile->write(writeBuf, msg.sizeMessage);
        if ( (this->writeFile->rdstate() & std::ofstream::badbit) != 0 ) {
            throw std::runtime_error("ostream::write error");
        }

        /* break loop if file fully received */
        if (n == msg.endIndex) {
            std::cout << "File received fully" << std::endl;
            break;
        }

        n +=1;
    }
}

QueueRx::~QueueRx(void) {
    /* close writeFile */
    this->writeFile->close();
    /* remove the queue */
    msgctl(this->qid, IPC_RMID, NULL);
}