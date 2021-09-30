#include "commandwatcher.hpp"
#include <iostream>

CommandWatcher::CommandWatcher()
: m_callbackCount(0)
{

}

void CommandWatcher::connect()
{

}

void CommandWatcher::disconnect()
{

}

void CommandWatcher::registerCallback(std::string str, void (*func)(std::string))
{
    m_callbackMap.insert(std::pair<int, Callback>(m_callbackCount, Callback(str, func)));
    ++m_callbackCount;
}

void CommandWatcher::deleteCallback(std::string, void (*func)(std::string))
{
    
}

void CommandWatcher::deleteCallback(int)
{

}

void CommandWatcher::showCallbacks()
{
    for (int i = 0; i < m_callbacks.size(); i++)
    {
        std::cout << "(" << i << ") - '" << m_callbackList;
    }
}

void CommandWatcher::startWatching()
{

}

void CommandWatcher::stopWatching()
{

}