#ifndef SHARED_MEMORY_SOCKET
#define SHARED_MEMORY_SOCKET

#if defined __linux__ || defined __APPLE__
    #include <sys/un.h>
#elif defined _WIN32

#endif

#include <string>

#include "neuromagshmeminfo.hpp"

namespace SharedMemory
{

class Socket
{
public:
    Socket();

    void connect(int sharedMemId, std::string clientPath, std::string serverPath);
    
    void disconnect();

    SharedMemory::Message getSharedMemoryMessage();
    
private:

    void setClientIDAndPath(int id, std::string path);

#if defined __linux__ || defined __APPLE__
    sockaddr_un getPOSIXSocketAddress();
#elif defined _WIN32

#endif

    int                 m_memId;
    int                 m_memSocket;

    std::string         m_clientPath;
};

}//namespace
#endif
