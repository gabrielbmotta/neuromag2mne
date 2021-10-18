#include "sharedmemorysocket.hpp"

#include <iostream>

#if defined __linux__ || defined __APPLE__
    #include <sys/stat.h>
    #include <sys/un.h>
    #include <sys/socket.h>
    #include <sys/shm.h>
#elif defined _WIN32

#endif

SharedMemorySocket::SharedMemorySocket()
{
}

bool SharedMemorySocket::connect(int sharedMemId, std::string clientPath, std::string serverPath)
{
    m_memId = sharedMemId;
    m_clientPath = clientPath;
    m_serverPath = serverPath;

    sockaddr_un address;
    
    if ((m_memSocket = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Unable to create socket.\n";
        return false;
    }

    memset(&address, 0, sizeof(address));

    char path[108];    
    sprintf (path,"%s%d",m_clientPath.c_str(),m_memId);
    strcpy(address.sun_path, path);

    address.sun_family = AF_UNIX;
    
    if (bind(m_memSocket, (sockaddr *)(&address), sizeof(address)) < 0) 
    {
        return false;
    }

    return true;
}

bool SharedMemorySocket::disconnect()
{
    return false;
}
