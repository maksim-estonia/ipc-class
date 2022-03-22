#ifndef IPC_CLASS_H
#define IPC_CLASS_H

#include <iostream>
#include <fstream>

/*
    The Product interface declares the operations that all concrete 
    products must implement.
*/
class ReceiverIPC {
    public:
        virtual ~ReceiverIPC() {}
        virtual std::string receive() const = 0;
};

class SenderIPC {
    public:
        virtual ~SenderIPC() {}
        virtual std::string send() const = 0;
};

/*
    Concrete Products provide various implementations
    of the Product interface
*/
class PipeRx: public ReceiverIPC {
    public:
        std::string receive() const override;
    private:
        std::string setupPipeRx() const;
        std::string fileSizeRx() const;
        std::string pipeRx() const;
};

class QueueRx: public ReceiverIPC {
    public:
        std::string receive() const override;
    private:
        std::string setupQueueRx() const;
        std::string fileSizeRx() const;
        std::string queueRx() const;
};

class ShmRx: public ReceiverIPC {
    public:
        std::string receive() const override;
    private:
        std::string setupShmRx() const;
        std::string fileSizeRx() const;
        std::string shmRx() const;
};

class PipeTx: public SenderIPC {
    std::fstream *file;
    public:
        PipeTx(std::fstream *file_in):file{file_in}{}
        std::string send() const override;
    private:
        std::string setupPipeTx() const;
        std::string fileSizeTx() const;
        std::string pipeTx() const;
};

class QueueTx: public SenderIPC {
    public:
        std::string send() const override;
    private:
        std::string setupQueueTx() const;
        std::string fileSizeTx() const;
        std::string queueTx() const;
};

class ShmTx: public SenderIPC {
    public:
        std::string send() const override;
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
        virtual ReceiverIPC* createIpcRx() const { return nullptr; };
        virtual SenderIPC* createIpcTx() const { return nullptr; };
        virtual SenderIPC* createIpcTx(std::fstream *) const { return nullptr; };
        /*
        Also note that, despite its name, the Creator's primary responsibility is
        not creating products. Usually, it contains some core business logic that
        relies on Product objects, returned by the factory method. Subclasses can 
        indirectly change that business logic by overriding the factory method and
        returning a different type of product from it.
        */
       std::string SomeOperation() const;
       std::string openWriteFile() const;
       std::fstream openReadFile(char *path) const;
};

/*
    Concrete Creators override the factory method in order to change the
    resulting product's type.
*/
class CreatorPipeRx: public CreatorIPC {
    /*
        Note that the signature of the method still uses the abstract product type,
        even though the concrete product is actually returned from the method.
        This way the Creator can stay independent of concrete product classes.
    */
    public:
        ReceiverIPC* createIpcRx() const override {
            return new PipeRx();
        }
};

class CreatorQueueRx: public CreatorIPC {
    public:
        ReceiverIPC* createIpcRx() const override {
            return new QueueRx();
        }
};

class CreatorShmRx: public CreatorIPC {
    public:
        ReceiverIPC* createIpcRx() const override {
            return new ShmRx();
        }
};

class CreatorPipeTx: public CreatorIPC {
    public:
        SenderIPC* createIpcTx(std::fstream *file_in) const override {
            return new PipeTx(file_in);
        }
};

class CreatorQueueTx: public CreatorIPC {
    public:
        SenderIPC* createIpcTx() const override {
            return new QueueTx();
        }
};

class CreatorShmTx: public CreatorIPC {
    public:
        SenderIPC* createIpcTx() const override {
            return new ShmTx();
        }
};

#endif