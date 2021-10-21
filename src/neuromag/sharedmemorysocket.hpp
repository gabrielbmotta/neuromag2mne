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

/*
A socket for communicating with the server part of the neuromag shared memory service.

Access incoming neuromag data, we need to ask the neuromag server where
this new data is being stored. We can request a struct that tells us where
in the shared memory block we can find data. This struct is what is returned
by 'getSharedMemoryMessage()', and can be used, once the location of the
shared memory block is also obtained (functionality that is not provided
by this class), to get the mPtr to the memory location of new data.
*/
class Socket
{
public:
    Socket();

    void connect(int sharedMemId, std::string clientPath);
    void disconnect();
    bool isConnected();

    SharedMemory::Message getSharedMemoryMessage();
    
private:
    void setClientIDAndPath(int id, std::string path);

#if defined __linux__ || defined __APPLE__
    sockaddr_un getPOSIXSocketAddress();
#endif

    int         mMemoryClientId;
    int         mSocketId;
    std::string mClientPath;
    bool        mIsConnected;
};
}//namespace
#endif
