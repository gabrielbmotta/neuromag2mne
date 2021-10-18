#ifndef TCP_SOCKET
#define TCP_SOCKET

#include <string>

class TCPSocket
{
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

