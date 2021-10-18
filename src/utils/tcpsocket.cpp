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

bool TCPSocket::connect(const char* addr, int port)
{
    while(m_isConnected){
        disconnect();
    }

#if defined __linux__ || defined __APPLE__
    m_socketID = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;

    server_address.sin_addr.s_addr = inet_addr(addr);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint>(port));

    if (::connect(m_socketID, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		std::cout << "Unable to connect to " << addr << ":" << port << "\n";
        return false;
    }
    else
    {
        std::cout << "Connected to " << addr << ":" << port << "\n";
        std::cout << "Socket ID: " << m_socketID << "\n";
        m_isConnected = true;
        return true;
    }
#elif defined _WIN32
    return false;
#endif
}

bool TCPSocket::disconnect()
{
    if(!m_isConnected)
    {
        return true;
    }

#if defined __linux__ || defined __APPLE__
    if(close(m_socketID) != 0)
    {
        return false;
    }
    else
    {
        m_isConnected = false;
        return true;
    }
#elif defined _WIN32
    return false;
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
    if(!m_isConnected)
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

