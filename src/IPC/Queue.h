#define ProjectId 123
#define PathName "input.txt"

typedef struct {
    long index;                 
    long endIndex;
    int sizeMessage;
    char payload[BUFFERSIZE_QUEUE];   /* bytes in the message */
} queuedMessage;