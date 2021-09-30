#include "datawatcher.hpp"
#include <iostream>

DataWatcher::DataWatcher()
{

}

void DataWatcher::startWatching()
{

}

void DataWatcher::stopWatching()
{

}

void DataWatcher::registerCallback(std::string str, void (*func)(char*))
{
    m_callbacks.push_back(DataCallback(str, func));
}

void DataWatcher::deleteCallback(std::string, void (*func)(char*))
{
    
}

void DataWatcher::deleteCallback(int index)
{
    if(index < m_callbacks.size()){
        m_callbacks.erase(m_callbacks.begin() + index);
    }
}

void DataWatcher::showCallbacks()
{
    for (int i = 0; i < m_callbacks.size(); i++)
    {
        std::cout << "(" << i << ") - '" << m_callbacks.at(i).m_trigger << "'\n";
    }
}