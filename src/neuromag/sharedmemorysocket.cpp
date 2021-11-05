#include "sharedmemorysocket.hpp"

#include <iostream>
#include <cstdio>
#include <unistd.h>

#if defined __linux__ || defined __APPLE__

#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/shm.h>

#elif defined _WIN32

#endif

#define SOCKET_MASK 0x000

/*
Constructs a Socket.
*/
sharedMemory::Socket::Socket()
        : mIsConnected(false)
{
}

/*
Connects socket to given client path with using given client id.

Does nothing if socket is already connected.
*/
void sharedMemory::Socket::connect(int sharedMemId, std::string clientPath)
{
  //std::cout << "PATH: " << clientPath << "\n";
  if(isConnected())
  {
    return;
  }

  mode_t old_mask = umask(SOCKET_MASK);

  setClientIDAndPath(sharedMemId, clientPath);
  sockaddr_un address = getPOSIXSocketAddress();

  unlink(address.sun_path);

  if((mSocketId = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
  {
    std::cout << "Unable to create socket.\n";
    umask(old_mask);
    return;
  }

  if(bind(mSocketId, (sockaddr *) (&address), sizeof(address)) < 0)
  {
    close(mSocketId);
    umask(old_mask);
    std::cout << "Unable to bind socket " << address.sun_path << "\n";
  }
  mIsConnected = true;
}

/*
Disconnects socket.

Does nothing if already disconnected.
*/
void sharedMemory::Socket::disconnect()
{
  if(!isConnected())
  {
    return;
  }
}

/*
Returns whether socket is connected.
*/
bool sharedMemory::Socket::isConnected()
{
  return mIsConnected;
}

/*
Gets message from neuromag shared memory server.

This message gives us where in the shared memory block we can find data.
*/
sharedMemory::Message sharedMemory::Socket::getSharedMemoryMessage()
{
  sharedMemory::Message msg;

  if(isConnected())
  {
    if(recv(mSocketId, (void *) (&msg), sizeof(msg), 0) == -1)
    {
      std::cout << "Unable to retrieve message.\n";
    }
  }

  return msg;
}

/*
Stores client ID and path.
*/
void sharedMemory::Socket::setClientIDAndPath(int id, std::string path)
{
  mMemoryClientId = id;
  mClientPath = path;
}

#if defined __linux__ || defined __APPLE__

/*
Generates POSIX struct for socket address.
*/
sockaddr_un sharedMemory::Socket::getPOSIXSocketAddress()
{
  sockaddr_un address;
  memset(&address, '\0', sizeof(address));
  address.sun_family = AF_UNIX;

  char path[108];
  sprintf(path, "%s%d", mClientPath.c_str(), mMemoryClientId);
  strcpy(address.sun_path, path);

  return address;
}

#endif
