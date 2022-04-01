#ifndef IPC_CLASS_H
#define IPC_CLASS_H

#include <iostream>
#include <fstream>
#include <memory>

// PIPE
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define PIPE_SIZE 1024
#define FIFO_FILE "/home/maksim/ipc-class/MYFIFO"

/*
    The Product interface declares the operations that all concrete 
    products must implement.
*/
class ReceiverIPC {
    public:
        virtual ~ReceiverIPC() {}
        virtual std::string receive() = 0;
};

class SenderIPC {
    public:
        virtual ~SenderIPC() {}
        virtual std::string send() = 0;
};

/*
    Concrete Products provide various implementations
    of the Product interface
*/
class PipeRx: public ReceiverIPC {
    std::fstream *file;
    int fd;
    char readbuf[PIPE_SIZE];
    int read_bytes;
    int size = 0;
    public:
        PipeRx(std::fstream *file_in):file{file_in}{}
        std::string receive() override;
    private:
        std::string setupPipeRx();
        std::string fileSizeRx();
        std::string pipeRx();
};

class QueueRx: public ReceiverIPC {
    public:
        std::string receive() override;
    private:
        std::string setupQueueRx() const;
        std::string fileSizeRx() const;
        std::string queueRx() const;
};

class ShmRx: public ReceiverIPC {
    public:
        std::string receive() override;
    private:
        std::string setupShmRx() const;
        std::string fileSizeRx() const;
        std::string shmRx() const;
};

class PipeTx: public SenderIPC {
    std::fstream *file;
    int fd;
    char readbuf[PIPE_SIZE];
    int size;
    public:
        PipeTx(std::fstream *file_in):file{file_in}{}
        std::string send() override;
    private:
        std::string setupPipeTx();
        std::string fileSizeTx();
        std::string pipeTx();
};

class QueueTx: public SenderIPC {
    public:
        std::string send() override;
    private:
        std::string setupQueueTx() const;
        std::string fileSizeTx() const;
        std::string queueTx() const;
};

class ShmTx: public SenderIPC {
    public:
        std::string send() override;
    private:
        std::string setupShmTx() const;
        std::string fileSizeTx() const;
        std::string shmTx() const;
};


/*
    The Creator class declares the factory method that is supposed to return an
    object of Product class. The Creator's subclasses usually provide
    the implementation of this method.
*/
class CreatorIPC{
    /*
        Note that the Creator may also provide some default implementation
        of the factory method.
    */
    public:
        virtual ~CreatorIPC(){};
        // virtual ReceiverIPC* createIpcRx() const { return nullptr; };
        // virtual ReceiverIPC* createIpcRx(std::fstream *) const { return nullptr; }
        // virtual SenderIPC* createIpcTx() const { return nullptr; };
        // virtual SenderIPC* createIpcTx(std::fstream *) const { return nullptr; };
        virtual std::unique_ptr<ReceiverIPC> createIpcRx() const { return nullptr; };
        virtual std::unique_ptr<ReceiverIPC> createIpcRx(std::fstream *) const { return nullptr; };
        virtual std::unique_ptr<SenderIPC> createIpcTx() const { return nullptr; };
        virtual std::unique_ptr<SenderIPC> createIpcTx(std::fstream *) const { return nullptr; };
        /*
        Also note that, despite its name, the Creator's primary responsibility is
        not creating products. Usually, it contains some core business logic that
        relies on Product objects, returned by the factory method. Subclasses can 
        indirectly change that business logic by overriding the factory method and
        returning a different type of product from it.
        */
       std::fstream openWriteFile(const char *path) const;
       std::fstream openReadFile(const char *path) const;
};

/*
    Concrete Creators override the factory method in order to change the
    resulting product's type.
*/
class CreatorPipeRx: public CreatorIPC {
    public:
        std::unique_ptr<ReceiverIPC> createIpcRx(std::fstream *file_in) const override {
            //return PipeRx(file_in);
            return std::make_unique<PipeRx>(file_in);
        }
};

class CreatorQueueRx: public CreatorIPC {
    public:
        std::unique_ptr<ReceiverIPC> createIpcRx() const override {
            return std::make_unique<QueueRx>();
        }
};

class CreatorShmRx: public CreatorIPC {
    public:
        std::unique_ptr<ReceiverIPC> createIpcRx() const override {
            return std::make_unique<ShmRx>();
        }
};

class CreatorPipeTx: public CreatorIPC {
    public:
        std::unique_ptr<SenderIPC> createIpcTx(std::fstream *file_in) const override {
            return std::make_unique<PipeTx>(file_in);
        }
};

class CreatorQueueTx: public CreatorIPC {
    public:
        std::unique_ptr<SenderIPC> createIpcTx() const override {
            return std::make_unique<QueueTx>();
        }
};

class CreatorShmTx: public CreatorIPC {
    public:
        std::unique_ptr<SenderIPC> createIpcTx() const override {
            return std::make_unique<ShmTx>();
        }
};

#endif