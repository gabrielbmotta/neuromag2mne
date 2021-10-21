#ifndef TCP_SOCKET
#define TCP_SOCKET

#if defined __linux__ || defined __APPLE__
#include <netinet/in.h>
#elif defined _WIN32
#endif

#include <string>

class TCPSocket
{
public:
    TCPSocket();

    void connect(const char* addr, int port);
    void disconnect();
    bool isConnected();

    void send(const std::string& msg);
    void send(const char* msg);

    std::string receive_blocking();

private:
    void setAddressAndPort(const char* addr, int port);
#if defined __linux__ || defined __APPLE__
    void setPOSIXSocketAddress();
#elif defined _WIN32
#endif

    std::string mAddress;
    int mPort;
    int mSocketId;
    bool mIsConnected;
    const int mReceivingBufferSize;
    sockaddr_in mServerAddress;
};

#endif

