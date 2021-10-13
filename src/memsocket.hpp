#ifndef SHMEM_SOCKET
#define SHMEM_SOCKET

#include "sharedmemorytypes.hpp"

class SharedMemorySocket{
public:
    SharedMemorySocket();
    bool connect();
    bool disconnect();
private:
int                 m_id;
SHAREDMEM::Block*   m_memBlock;
};

#endif