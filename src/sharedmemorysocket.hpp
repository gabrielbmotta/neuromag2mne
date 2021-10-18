#ifndef SHAREDMEM_SOCKET
#define SHAREDMEM_SOCKET

#include <string>

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
};

#endif
