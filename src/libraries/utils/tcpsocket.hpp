#ifndef NEUROMAG2MNE_TCPSOCKET_HPP
#define NEUROMAG2MNE_TCPSOCKET_HPP

#include "utils_global.hpp"

#if defined __linux__ || defined __APPLE__
#include <netinet/in.h>
#elif defined _WIN32
#endif

#include <string>

class TCPSocket
{
public:
  TCPSocket();
  ~TCPSocket();

  void connect(const char* addr, unsigned short int port);
  void connect(std::string addr, unsigned short int port);
  void disconnect();
  bool isConnected() const;

  void send(const std::string& msg);
  void send(const char* msg);
  void send(const char* msg, size_t size);
  void send(const void* msg, size_t size);

  std::string receive_blocking();
  //todo: create non-blocking receive function

private:
  void setAddressAndPort(const char* addr, unsigned short int port);
#if defined __linux__ || defined __APPLE__
  void setPOSIXSocketAddress();
#elif defined _WIN32
#endif

  std::string mAddress;
  unsigned short int mPort;
  int mSocketId;
  bool mIsConnected;
  const unsigned long int mReceivingBufferSize;
  sockaddr_in mServerAddress;
};

#endif

