#include "sharedmemorysocket.hpp"

#include <iostream>
#include <cstdio>

#if defined __linux__ || defined __APPLE__
    #include <sys/stat.h>
    #include <sys/un.h>
    #include <sys/socket.h>
    #include <sys/shm.h>
#elif defined _WIN32

#endif


SharedMemory::Socket::Socket()
{
}

void SharedMemory::Socket::connect(int sharedMemId, std::string clientPath, std::string serverPath)
{
    setClientIDAndPath(sharedMemId, clientPath);
    
    if ((m_memSocket = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Unable to create socket.\n";
        return;
    }

     sockaddr_un address = getPOSIXSocketAddress();
    
    if (bind(m_memSocket, (sockaddr *)(&address), sizeof(address)) < 0) 
    {
        std::cout << "Unable to bind socket.\n";
    }
}

void SharedMemory::Socket::disconnect()
{
}

SharedMemory::Message SharedMemory::Socket::getSharedMemoryMessage()
{
    SharedMemory::Message msg;

    if(recv(m_memSocket, (void*)(&msg), sizeof(msg), 0) == -1)
    {
        std::cout << "Unable to retrieve message.\n";
    }

    return msg;
}

void SharedMemory::Socket::setClientIDAndPath(int id, std::string path)
{
    m_memId = id;
    m_clientPath = path;
}

sockaddr_un SharedMemory::Socket::getPOSIXSocketAddress()
{
    sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;

    char path[108];    
    sprintf (path,"%s%d",m_clientPath.c_str(),m_memId);
    strcpy(address.sun_path, path);

    return address;
}
