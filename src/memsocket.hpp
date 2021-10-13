#ifndef SHMEM_SOCKET
#define SHMEM_SOCKET

class SharedMemorySocket{
public:
    SharedMemorySocket();
    bool connect();
    bool disconnect();
};

#endif