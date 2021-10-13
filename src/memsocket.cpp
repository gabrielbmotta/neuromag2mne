#include "memsocket.hpp"

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

bool SharedMemorySocket::connect()
{
    int sock = -1;
    sockaddr_un address;
    if ((sock = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        std::cout << "Unable to create socket.\n";
        return false;

    }
    return false;
}

bool SharedMemorySocket::disconnect()
{
    return false;
}