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
    int i = 0;
    std::vector<DataCallback>::iterator it;

    for(it = m_callbacks.begin(); it != m_callbacks.end(); it++, i++)
    {
        std::cout << "(" << i << ") - '" << m_callbacks.at(i).m_trigger << "'\n";
    }
}