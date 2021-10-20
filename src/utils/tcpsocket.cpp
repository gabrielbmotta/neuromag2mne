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
:m_socketID(0)
,m_isConnected(false)
{
}

void TCPSocket::connect(const char* addr, int port)
{
    if (isConnected())
    {
        return;
    }

    setAddressAndPort(addr, port);

#if defined __linux__ || defined __APPLE__
    m_socketID = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address = getPOSIXSocketAddress();

    if (::connect(m_socketID, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		std::cout << "Unable to connect to " << addr << ":" << port << "\n";
    }
    else
    {
        std::cout << "Connected to " << addr << ":" << port << "\n";
        m_isConnected = true;
    }
#elif defined _WIN32
#endif
}

void TCPSocket::disconnect()
{
    if(!isConnected())
    {
        return;
    }

#if defined __linux__ || defined __APPLE__
    if(close(m_socketID) != 0)
    {
        std::cout << "Unable to disconnect socket.\n";
    }
    else
    {
        m_isConnected = false;
    }
#elif defined _WIN32
#endif
}

bool TCPSocket::isConnected()
{
    return m_isConnected;
}

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

    if(::send(m_socketID, msg, strlen(msg), 0) < 0)
	{
		std::cout << "Failed to send message: " << msg << "\n";
	}
#elif defined _WIN32

#endif
}

std::string TCPSocket::receive_blocking()
{
#if defined __linux__ || defined __APPLE__

    const int reply_size = 10000;
    char reply[reply_size];
    memset(reply, '\0', sizeof(char) * reply_size);
    if(recv(m_socketID, reply, reply_size, 0) < 0)
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

void TCPSocket::setAddressAndPort(const char* addr, int port)
{
    mAddress = addr;
    mPort = port;
}

#if defined __linux__ || defined __APPLE__
sockaddr_in TCPSocket::getPOSIXSocketAddress()
{
    sockaddr_in server_address;

    server_address.sin_addr.s_addr = inet_addr(mAddress.c_str());
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint>(mPort));

    return server_address;
}
#elif defined _WIN32
#endif