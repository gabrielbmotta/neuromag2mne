#include "commandwatcher.hpp"
#include "socket.hpp"
#include <iostream>
#include <unistd.h>

void* watchCommands(void* input)
{
    CommandWatcher* ptr = static_cast<CommandWatcher*>(input);
    while (true)
    {
        std::cout << "HI! \n";
        ptr->showCallbacks();
        sleep(1);
    }
    
    return NULL;
}

CommandWatcher::CommandWatcher()
: m_isWatching(false)
, m_isConnected(false)
{

}

void CommandWatcher::connect()
{
    CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

void CommandWatcher::connect(int port, std::string password)
{
    m_tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;

    server_address.sin_addr.s_addr = inet_addr(COLLECTOR_ADDR);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(COLLECTOR_PORT);

    if (::connect(m_tcpSocket , (struct sockaddr *)&server_address , sizeof(server_address)) < 0)
	{
		std::cout << "Unable to connect to " << COLLECTOR_ADDR << ":" << COLLECTOR_PORT << "\n";
	}
    else
    {
        std::cout << "Connected to" << COLLECTOR_ADDR << ":" << COLLECTOR_PORT << "\n";
        std::cout << "Socket ID: " << m_tcpSocket << "\n";
    }
}

void CommandWatcher::disconnect()
{

}

void CommandWatcher::registerCallback(std::string str, void (*func)(std::string))
{
    if(m_isWatching)
    {
        std::cout << "Unable to register callback while watching.\n";
    }
    else 
    {
        m_callbacks.push_back(CommandCallback(str, func));
    }
}

void CommandWatcher::deleteCallback(std::string, void (*func)(std::string))
{
    
}

void CommandWatcher::deleteCallback(int index)
{
    if(index < m_callbacks.size()){
        m_callbacks.erase(m_callbacks.begin() + index);
    }
}

void CommandWatcher::showCallbacks()
{
    int i = 0;
    std::vector<CommandCallback>::iterator it;

    for(it = m_callbacks.begin(); it != m_callbacks.end(); it++, i++)
    {
        std::cout << "(" << i << ") - '" << m_callbacks.at(i).m_trigger << "'\n";
    }
}

void CommandWatcher::startWatching()
{
    if(pthread_create(&m_thread, NULL, watchCommands, this))
    {
        std::cout << "Unable to start CommandWatcehr thread;\n";
        return;
    }
    m_isWatching = true;
}

void CommandWatcher::stopWatching()
{
    std::cout  <<  "StopWatching\n";
    if (pthread_cancel(this->m_thread))
    {
        std::cout << "Unable to stop CommandWatcehr thread;\n";
        return;
    }
    m_isWatching = false;
}

bool CommandWatcher::isWatching()
{
    return m_isWatching;
}

