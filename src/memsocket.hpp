#ifndef SHMEM_SOCKET
#define SHMEM_SOCKET

#include <string>

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
}

class SharedMemorySocket
{
public:
    SharedMemorySocket();
    bool connect(int sharedMemId, std::string clientPath, std::string serverPath);
    bool disconnect();
private:

    int                 m_memId;
    int                 m_memSocket;

    std::string         m_clientPath;
    std::string         m_serverPath;

    SHAREDMEM::Block*   m_memBlock;
};

#endif