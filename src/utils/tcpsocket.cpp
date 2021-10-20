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


TCPSocket::TCPSocket()
  : mSocketId(0)
  , mIsConnected(false)
  , mReceivingBufferSize(16348)
{
}

bool TCPSocket::connect(const char* addr, int port)
{
  while(mIsConnected)
  {
    disconnect();
  }

#if defined __linux__ || defined __APPLE__
  mSocketId = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server_address;

  //todo initialize server address as member var and methods
  server_address.sin_addr.s_addr = inet_addr(addr);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(static_cast<uint>(port));

  if (::connect(mSocketId, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    std::cout << "Unable to connect to " << addr << ":" << port << "\n";
    return false;
  }
  else
  {
    std::cout << "Connected to " << addr << ":" << port << "\n";
    std::cout << "Socket ID: " << mSocketId << "\n";
    mIsConnected = true;
    return true;
  }
#elif defined _WIN32
  return false;
#endif
}

bool TCPSocket::disconnect()
{
  if(!mIsConnected)
  {
    return true;
  }

#if defined __linux__ || defined __APPLE__
  if(close(mSocketId) != 0)
  {
    return false;
  }
  else
  {
    mIsConnected = false;
    return true;
  }
#elif defined _WIN32
  return false;
#endif
}

bool TCPSocket::isConnected()
{
  return mIsConnected;
}

void TCPSocket::send(const std::string& msg)
{
  send(msg.c_str());
}

void TCPSocket::send(const char* msg)
{
  if(!mIsConnected)
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

std::string TCPSocket::receive_blocking()
{
#if defined __linux__ || defined __APPLE__

  //todo create member buffer and initialize fcns.
  char reply[mReceivingBufferSize];
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

//todo create this member function
//void TCPSocket::obtainSocketId()
//{
//
//}
