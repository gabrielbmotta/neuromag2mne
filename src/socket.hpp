#ifndef NETWORK_SOCKET
#define NETWORK_SOCKET

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

class TCPSocket{
public:
    TCPSocket() = default;
    bool connect(const char* addr, int port);
    bool disconnect();

private:
    int m_socketID;
};

#endif