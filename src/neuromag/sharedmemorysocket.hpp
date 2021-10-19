#ifndef SHARED_MEMORY_SOCKET
#define SHARED_MEMORY_SOCKET

#include <string>

#include "neuromagshmeminfo.hpp"

namespace SharedMemory
{

class Socket
{
public:
    Socket();
    bool connect(int sharedMemId, std::string clientPath, std::string serverPath);
    bool disconnect();

    SharedMemory::Message getSharedMemoryMessage();
    
private:


    int                 m_memId;
    int                 m_memSocket;

    std::string         m_clientPath;
    std::string         m_serverPath;
};

}//namespace
#endif
