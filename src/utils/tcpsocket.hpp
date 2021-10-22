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

    void connect(const char* addr, unsigned int port);
    void disconnect();
    bool isConnected();

    void send(const std::string& msg);
    void send(const char* msg);

    std::string receive_blocking();

private:
    void setAddressAndPort(const char* addr, unsigned int port);
#if defined __linux__ || defined __APPLE__
    void setPOSIXSocketAddress();
#elif defined _WIN32
#endif

    std::string mAddress;
    unsigned int mPort;
    int mSocketId;
    bool mIsConnected;
    const unsigned long int mReceivingBufferSize;
    sockaddr_in mServerAddress;
};

#endif

