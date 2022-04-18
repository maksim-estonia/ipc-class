#ifndef IPC_CLASS_H
#define IPC_CLASS_H

#include <fstream>  /* std::fstream */
#include <memory>   /* unique_ptr */

#define BUFFERSIZE  1024 

/*
    The Product interface declares the operations that all concrete 
    products must implement.
*/
class ReceiverIPC {
    public:
        virtual ~ReceiverIPC() {}
        virtual void receive() = 0;
};

class SenderIPC {
    public:
        virtual ~SenderIPC() {}
        virtual void send() = 0;
};

/*
    Concrete Products provide various implementations
    of the Product interface
*/
class PipeRx: public ReceiverIPC {
    std::fstream *writeFile;
    int fd; /* file descriptor pipe */

    public:
        PipeRx(std::fstream *file_in):writeFile{file_in}{}
        void receive() override;
        ~PipeRx();
    private:
        void setupPipeRx();
        void pipeRx();
};

class QueueRx: public ReceiverIPC {
    std::fstream *writeFile;
    int qid;

    public:
        QueueRx(std::fstream *file_in):writeFile{file_in}{}
        void receive() override;
        ~QueueRx();
    private:
        void setupQueueRx();
        void queueRx();
};

class ShmRx: public ReceiverIPC {
    public:
        void receive() override;
    private:
        void setupShmRx() const;
        void fileSizeRx() const;
        void shmRx() const;
};

class PipeTx: public SenderIPC {
    std::fstream *readFile;
    int fd;     /* file descriptor pipe */

    public:
        PipeTx(std::fstream *file_in):readFile{file_in}{}
        void send() override;
        ~PipeTx();
    private:
        void setupPipeTx();
        void pipeTx();
};

class QueueTx: public SenderIPC {
    std::fstream *readFile;
    int qid;

    public:
        QueueTx(std::fstream *file_in):readFile{file_in}{}
        void send() override;
        ~QueueTx();
    private:
        void setupQueueTx();
        void queueTx();
};

class ShmTx: public SenderIPC {
    public:
        void send() override;
    private:
        void setupShmTx() const;
        void fileSizeTx() const;
        void shmTx() const;
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
            return std::make_unique<PipeRx>(file_in);
        }
};

class CreatorQueueRx: public CreatorIPC {
    public:
        std::unique_ptr<ReceiverIPC> createIpcRx(std::fstream *file_in) const override {
            return std::make_unique<QueueRx>(file_in);
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
        std::unique_ptr<SenderIPC> createIpcTx(std::fstream *file_in) const override {
            return std::make_unique<QueueTx>(file_in);
        }
};

class CreatorShmTx: public CreatorIPC {
    public:
        std::unique_ptr<SenderIPC> createIpcTx() const override {
            return std::make_unique<ShmTx>();
        }
};

#endif