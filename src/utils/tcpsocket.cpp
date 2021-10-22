#include <iostream>
#include <cstring>

#include "tcpsocket.hpp"

#if defined __linux__ || defined __APPLE__
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#elif defined _WIN32

#endif

/*
Creates a TCP Socket
*/

#define SOCKET_BUFFER_LEN 16348

TCPSocket::TCPSocket()
  : mPort(0)
  , mSocketId(0)
  , mIsConnected(false)
  , mReceivingBufferSize(SOCKET_BUFFER_LEN)
{
}

/*
Connects to an address and port given by the input parameters.

Does nothing if the instance of TCPSocket is already connected.
*/
void TCPSocket::connect(const char* addr, unsigned int port)
{
    if (isConnected())
    {
        return;
    }

    setAddressAndPort(addr, port);

#if defined __linux__ || defined __APPLE__
    mSocketId = socket(AF_INET, SOCK_STREAM, 0);

    setPOSIXSocketAddress();

    if ( ::connect(mSocketId,
                  (struct sockaddr *) &mServerAddress,
                      sizeof(mServerAddress)) < 0 )
	{
		std::cout << "Unable to connect to " << addr << ":" << port << "\n";
    } else {
        std::cout << "Connected to " << addr << ":" << port << "\n";
        mIsConnected = true;
    }
#elif defined _WIN32
#endif
}

/*
Disconnects the socket.

Does nothing if not connected.
*/
void TCPSocket::disconnect()
{
    if(!isConnected())
    {
        return;
    }

#if defined __linux__ || defined __APPLE__
    if(close(mSocketId) != 0)
    {
        std::cout << "Unable to disconnect socket.\n";
    }
    else
    {
        mIsConnected = false;
    }
#elif defined _WIN32
#endif
}

/*
Returns whether the socket is connected.
*/
bool TCPSocket::isConnected()
{
  return mIsConnected;
}

/*
Sends a message containing input paramter.

Does nothing if socket is not connected.
*/
void TCPSocket::send(const std::string& msg)
{
  send(msg.c_str());
}

void TCPSocket::send(const char* msg)
{
    if(!isConnected())
    {
        std::cout << "Message not sent, not connected.\n";
        return;
    }
#if defined __linux__ || defined __APPLE__

  if(::send(mSocketId, msg, strlen(msg), 0) < 0)
  {
    std::cout << "Failed to send message: " << msg << "\n";
  }
#elif defined _WIN32

#endif
}

/*
Reads available data from socket.

Does nothing if socket is not connected.
*/
std::string TCPSocket::receive_blocking()
{
  
    if(!isConnected())
    {
        std::cout << "Not connected, nothing to receive.\n";
        return std::string();
    }
#if defined __linux__ || defined __APPLE__
    //todo create member buffer and initialize fcns.
    char reply[SOCKET_BUFFER_LEN];
    memset(reply, '\0', sizeof(char) * mReceivingBufferSize);
    if(recv(mSocketId, reply, mReceivingBufferSize, 0) < 0)
    {
      std::cout << "Unable to receive reply from server.\n";
      return std::string();
    }
    else
    {
//  	  std::cout <<"\n==========START \n";
//        std::cout << reply;
//	  std::cout <<"==========END \n"; 
    return std::string(reply);
    }
#elif defined _WIN32
  return std::string();
#endif
}

/*
Stores address and port information.
*/
void TCPSocket::setAddressAndPort(const char* addr, unsigned int port)
{
    mAddress = addr;
    mPort = port;
}

#if defined __linux__ || defined __APPLE__
/*
Generates a sockaddr_in struct and populates it with stored address and port information.
*/
void TCPSocket::setPOSIXSocketAddress()
{
  mServerAddress.sin_addr.s_addr = inet_addr(mAddress.c_str());
  mServerAddress.sin_family = AF_INET;
  mServerAddress.sin_port = htons(mPort);
}
#elif defined _WIN32
#endif
