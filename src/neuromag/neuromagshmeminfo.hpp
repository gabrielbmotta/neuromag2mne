#ifndef SHARED_MEMORY_INFO
#define SHARED_MEMORY_INFO

#define SERVER_PATH         "/neuro/dacq/sockets/dacq_server"
#define CLIENT_PATH         "/neuro/dacq/sockets/dacq_client_"
#define CLIENT_ID           13014

#define SHMEM_MAX_DATA      500*1500*4
#define SHMEM_NUM_BLOCKS    100
#define SHMEM_NO_BUF        -1

namespace SHAREDMEM{
struct Client{
    int client_id;
    int done;
};

struct Block{
    Client clients[SHMEM_NUM_BLOCKS];
    unsigned char data[SHMEM_MAX_DATA];
};

struct Message{
    int kind;
    int type;
    int size;
    int loc;
    int shmem_buf;
    int shmem_loc;
};
}//namespace
#endif
