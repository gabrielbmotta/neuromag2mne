#include "commandwatcher.hpp"
#include <iostream>

CommandWatcher::CommandWatcher()
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
    m_callbacks.push_back(Callback(str, func));
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
        std::cout << "(" << i << ") - '" << m_callbacks.at(i).command << "'\n";
    }
}

void CommandWatcher::startWatching()
{

}

void CommandWatcher::stopWatching()
{

}