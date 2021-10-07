#include "commandwatcher.hpp"
#include "socket.hpp"
#include <iostream>
#include <unistd.h>

void* watchCommands(void* input)
{
    CommandWatcher* ptr = static_cast<CommandWatcher*>(input);
    ptr->m_socket.send(TELNET_CMD_MONI);

    while (true)
    {
        std::string reply = ptr->m_socket.receive_blocking();
        if (reply.size())
        {
            std::cout << "We've recieved a message!\n";
        }
        
        ptr->showCallbacks();
        sleep(1);
    }
    
    return NULL;
}

CommandWatcher::CommandWatcher()
: m_state(DISCONNECTED_NOT_WATCHING)
{

}

void CommandWatcher::connect()
{
    CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

void CommandWatcher::connect(int port, std::string password)
{
    if(m_state != DISCONNECTED_NOT_WATCHING){
        disconnect();
    }

    m_socket.connect(COLLECTOR_ADDR, COLLECTOR_PORT);
    m_socket.send(TELNET_CMD_PASS);
    m_socket.send(TELNET_CMD_NAME);
}

void CommandWatcher::disconnect()
{
    if(m_state != DISCONNECTED_NOT_WATCHING){
        stopWatching();
        m_socket.disconnect();
        m_state = DISCONNECTED_NOT_WATCHING;
    }
}

void CommandWatcher::registerCallback(std::string str, void (*func)(std::string))
{
    if(m_state = CONNECTED_WATCHING)
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
    if(m_state == CONNECTED_NOT_WATCHING){
        if(pthread_create(&m_thread, NULL, watchCommands, this))
        {
            std::cout << "Unable to start CommandWatcehr thread;\n";
            return;
        }
        m_state = CONNECTED_WATCHING;
    }
}

void CommandWatcher::stopWatching()
{
    if(m_state == CONNECTED_WATCHING){
        std::cout  <<  "StopWatching\n";
        if (pthread_cancel(this->m_thread))
        {
            std::cout << "Unable to stop CommandWatcehr thread;\n";
            return;
        }
        m_state = CONNECTED_NOT_WATCHING;
    }
}

CommandWatcher::state CommandWatcher::getState()
{
    return m_state;
}