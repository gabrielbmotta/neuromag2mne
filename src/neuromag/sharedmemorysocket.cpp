#include "sharedmemorysocket.hpp"

#include <iostream>

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

bool SharedMemory::Socket::connect(int sharedMemId, std::string clientPath, std::string serverPath)
{
    m_memId = sharedMemId;
    m_clientPath = clientPath;
    m_serverPath = serverPath;
    
    if ((m_memSocket = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Unable to create socket.\n";
        return false;
    }

    sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;

    char path[108];    
    sprintf (path,"%s%d",m_clientPath.c_str(),m_memId);
    strcpy(address.sun_path, path);
    
    if (bind(m_memSocket, (sockaddr *)(&address), sizeof(address)) < 0) 
    {
        std::cout << "Unable to bind socket.\n";
        return false;
    }

    return true;
}

bool SharedMemory::Socket::disconnect()
{
    return false;
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
