#define ProjectId 123
#define PathName "send_main"

typedef struct {
    long index;                 
    long endIndex;
    int sizeMessage;
    char payload[BUFFERSIZE_QUEUE];   /* bytes in the message */
} queuedMessage;