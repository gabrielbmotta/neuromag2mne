#include "datawatcher.hpp"
#include <iostream>

void* watchData(void* input)
{
    return NULL;
}

DataWatcher::DataWatcher()
: m_isWatching(false)
{

}

void DataWatcher::connect()
{

}

void DataWatcher::disconnet()
{
    
}

void DataWatcher::registerCallback(std::string str, void (*func)(char*))
{
    if(m_isWatching)
    {
        std::cout << "Unable to register callback while watching.\n";
    }
    else
    {
        m_callbacks.push_back(DataCallback(str, func));
    }
}

void DataWatcher::deleteCallback(std::string, void (*func)(char*))
{
    
}

void DataWatcher::deleteCallback(int index)
{
    if(static_cast<unsigned int>(index) < m_callbacks.size()){
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

void DataWatcher::startWatching()
{
    if(m_thread.startThread(watchData, this))
    {
        m_isWatching = true;
    }
}

void DataWatcher::stopWatching()
{
    if(m_thread.stopThread())
    {
        m_isWatching = false;
    }
}

bool DataWatcher::isWatching()
{
    return m_isWatching;
}

