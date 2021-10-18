#ifndef SHARED_MEMORY_SOCKET
#define SHARED_MEMORY_SOCKET

#include <string>

namespace SharedMemory
{

class Socket
{
public:
    Socket();
    bool connect(int sharedMemId, std::string clientPath, std::string serverPath);
    bool disconnect();
    
private:

    int                 m_memId;
    int                 m_memSocket;

    std::string         m_clientPath;
    std::string         m_serverPath;
};

}//namespace
#endif
