#include "commandwatcher.hpp"
#include <iostream>

CommandWatcher::CommandWatcher()
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
    m_callbacks.push_back(CommandCallback(str, func));
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
    for (int i = 0; i < m_callbacks.size(); i++)
    {
        std::cout << "(" << i << ") - '" << m_callbacks.at(i).m_trigger << "'\n";
    }
}

void CommandWatcher::startWatching()
{

}

void CommandWatcher::stopWatching()
{

}