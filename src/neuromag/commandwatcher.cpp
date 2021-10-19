#include "commandwatcher.hpp"
#include "../utils/tcpsocket.hpp"
#include <iostream>
#include <unistd.h>

void* Neuromag::watchCommands(void* input)
{
    CommandWatcher* ptr = static_cast<CommandWatcher*>(input);
    ptr->m_socket.send(TELNET_CMD_MONI);

    while (true)
    {
        std::string reply = ptr->m_socket.receive_blocking();
        if (reply.size())
        {
            //std::cout << "We've recieved a message! -- " << reply << "\n";
            ptr->checkForCallbacks(reply);
        }
        
        //ptr->showCallbacks();
        //sleep(1);
    }

    std::cout << "Exiting watch loop.\n";
    
    return NULL;
}

Neuromag::CommandWatcher::CommandWatcher()
: m_state(DISCONNECTED_NOT_WATCHING)
{

}

void Neuromag::CommandWatcher::connect()
{
    CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

void Neuromag::CommandWatcher::connect(int port, std::string password)
{
    if(m_state != DISCONNECTED_NOT_WATCHING)
    {
        disconnect();
    }

    m_socket.connect(COLLECTOR_ADDR, COLLECTOR_PORT);
//    std::cout << m_socket.receive_blocking() << "\n";
    m_socket.receive_blocking();

//    std::cout << "Sending password...\n";
    m_socket.send(TELNET_CMD_PASS);
//    std::cout << m_socket.receive_blocking() << "\n";
    m_socket.receive_blocking();

//    std::cout << "Sending name...\n";
    m_socket.send(TELNET_CMD_NAME);
//    std::cout << m_socket.receive_blocking() << "\n";
    m_socket.receive_blocking();

    m_state = CONNECTED_NOT_WATCHING;
}

void Neuromag::CommandWatcher::disconnect()
{
    if(m_state != DISCONNECTED_NOT_WATCHING)
    {
        stopWatching();
        m_socket.disconnect();
        m_state = DISCONNECTED_NOT_WATCHING;
    }
}

void Neuromag::CommandWatcher::registerCallback(std::string str, void (*func)(void*), void* call)
{
    if( m_state == CONNECTED_WATCHING )
    {
        std::cout << "Unable to register callback while watching.\n";
    }
    else 
    {
        m_callbacks.push_back(stringCallbackPair(str, func, call));
    }
}

void Neuromag::CommandWatcher::deleteCallback(std::string str, void (*func)(void*), void* call)
{
    for ( std::vector<stringCallbackPair>::iterator it = m_callbacks.begin(); 
          it != m_callbacks.end(); ++it)
        {
            if( *it == stringCallbackPair(str,func,call))
            {
                m_callbacks.erase(it);
            }
        }
}

void Neuromag::CommandWatcher::showCallbacks()
{
    int i = 0;
    std::vector<stringCallbackPair>::iterator it;

    for(it = m_callbacks.begin(); it != m_callbacks.end(); it++, i++)
    {
        std::cout << "(" << i << ") - '" << it->trigger_string << " " << it->callback << "'\n";
    }
}

void Neuromag::CommandWatcher::startWatching()
{
    if(m_state == CONNECTED_NOT_WATCHING){
        if(m_thread.startThread(watchCommands, this))
        {
            m_state = CONNECTED_WATCHING;
        }
    }
}

void Neuromag::CommandWatcher::stopWatching()
{
    if(m_state == CONNECTED_WATCHING){
        if (m_thread.stopThread())
        {
            m_state = CONNECTED_NOT_WATCHING;
        }
    }
}

Neuromag::CommandWatcher::state Neuromag::CommandWatcher::getState()
{
    return m_state;
}

void Neuromag::CommandWatcher::checkForCallbacks(std::string msgString)
{
    std::vector<stringCallbackPair>::iterator it;

    for(it = m_callbacks.begin(); it != m_callbacks.end(); it++)
    {
        if(msgString.find(it->trigger_string) != -1){
            std::cout << "We've received a message containing " << it->trigger_string << ".\n";
            it->callback(it->objPtr);
        }
    }
}
