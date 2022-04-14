#include <iostream>
#include "IPC.h"

#include "Queue.h"

#include <sys/stat.h>   /* S_IRWXU S_IRWXG */
#include <sys/ipc.h>    /* IPC_CREAT */
#include <sys/msg.h>    /* msgget() */
#include <string.h>     /* strerror() */

void QueueRx::receive(void) {
    this->setupQueueRx();

    this->queueRx();
}

void QueueRx::setupQueueRx(void) {
    key_t key;

    /* setup message queue */
    key = ftok(PathName, ProjectId);    /* key to identify the queue */
    if (key<0) {
        std::cout << "ftok error" << std::endl;
        throw std::runtime_error(strerror(errno));
    }

    this->qid = msgget(key, S_IRWXU | S_IRWXG | IPC_CREAT);
    if (this->qid < 0) {
        std::cout << "msgget" << std::endl;
        throw std::runtime_error(strerror(errno));
    }

}

void QueueRx::queueRx(void) {
    int n = 1;
    char writeBuf[BUFFERSIZE_QUEUE];

    while (1) {
        queuedMessage msg;

        if (msgrcv(this->qid, &msg, sizeof(msg), n, MSG_NOERROR | IPC_NOWAIT) < 0) {
            throw std::runtime_error(strerror(errno));
        }

        strcpy(writeBuf, msg.payload);
        std::cout << "---------" << std::endl;
        std::cout << "index: " << msg.index << std::endl;
        std::cout << "sizeMessage: " << msg.sizeMessage << std::endl;
        std::cout << writeBuf << std::endl;
        std::cout << "endIndex: " << msg.endIndex << std::endl;
        std::cout << "---------" << std::endl;
        this->writeFile->write(writeBuf, msg.sizeMessage);

        /* break loop if file fully received */
        if (msg.index == msg.endIndex) {
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