#ifndef NETWORK_SOCKET
#define NETWORK_SOCKET

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class TCPSocket{
public:
    TCPSocket();
    bool connect(const char* addr, int port);
    bool disconnect();
    bool isConnected();
    void send(const std::string& msg);
    void send(const char* msg);
    std::string receive_blocking();

private:
    int m_socketID;
    bool m_isConnected;
};

#endif

