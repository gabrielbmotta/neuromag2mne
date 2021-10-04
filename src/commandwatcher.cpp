#include "commandwatcher.hpp"
#include <iostream>
#include <unistd.h>

void* watchCommands(void* input)
{
    CommandWatcher* ptr = static_cast<CommandWatcher*>(input);
    while (true)
    {
        std::cout << "HI! \n";
        sleep(1);
    }
    
    return NULL;
}

CommandWatcher::CommandWatcher()
: m_isWatching(false)
{

}

void CommandWatcher::connect()
{
    connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

void CommandWatcher::connect(int port, std::string password)
{

}

void CommandWatcher::disconnect()
{

}

void CommandWatcher::registerCallback(std::string str, void (*func)(std::string))
{
    if(m_isWatching)
    {
        m_callbacks.push_back(CommandCallback(str, func));
        std::cout << "Unable to register callback while watching.\n";
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