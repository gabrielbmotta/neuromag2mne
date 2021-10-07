#include <iostream>
#include <cstring>

#include "socket.hpp"

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
        std::cout << "Connected to" << addr << ":" << port << "\n";
        std::cout << "Socket ID: " << m_socketID << "\n";
        m_isConnected = true;
        return true;
    }
}

bool TCPSocket::disconnect()
{
    if(!m_isConnected)
    {
        return true;
    }

    if(close(m_socketID) != 0)
    {
        return false;
    }
    else
    {
        m_isConnected = false;
        return true;
    }
}

bool TCPSocket::isConnected()
{
    return m_isConnected;
}

void TCPSocket::send(const char* msg)
{
    if(!m_isConnected)
    {
        return;
    }

    if(::send(m_socketID, msg, strlen(msg), 0) < 0)
	{
		std::cout << "Failed to send message: " << msg << "\n";
	}
}