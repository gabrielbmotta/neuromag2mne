#include "datawatcher.hpp"
#include "neuromagshmeminfo.hpp"

#include <iostream>

void* Neuromag::watchData(void* input)
{
    DataWatcher* ptr = static_cast<DataWatcher*>(input);
    //ptr.
    return NULL;
}

Neuromag::DataWatcher::DataWatcher()
: m_isWatching(false)
{
}

void Neuromag::DataWatcher::connect()
{
    m_memManager.setParameters(SharedMemory::Parameters::neuromagDefault());
    m_memManager.connect();
}

void Neuromag::DataWatcher::disconnet()
{
    
}

void Neuromag::DataWatcher::registerCallback(void (*func)(void*))
{
    // if(m_isWatching)
    // {
    //     std::cout << "Unable to register callback while watching.\n";
    // }
    // else
    // {
    //     m_callbacks.push_back(DataCallback(str, func));
    // }
}

void Neuromag::DataWatcher::deleteCallback(void (*func)(void*))
{
    
}

void Neuromag::DataWatcher::deleteCallback(int index)
{
    // if(static_cast<unsigned int>(index) < m_callbacks.size()){
    //     m_callbacks.erase(m_callbacks.begin() + index);
    // }
}

void Neuromag::DataWatcher::showCallbacks()
{
    // int i = 0;
    // std::vector<DataCallback>::iterator it;

    // for(it = m_callbacks.begin(); it != m_callbacks.end(); it++, i++)
    // {
    //     std::cout << "(" << i << ") - '" << m_callbacks.at(i).m_trigger << "'\n";
    // }
}

void Neuromag::DataWatcher::startWatching()
{
    if(m_thread.startThread(watchData, this))
    {
        m_isWatching = true;
    }
}

void Neuromag::DataWatcher::stopWatching()
{
    if(m_thread.stopThread())
    {
        m_isWatching = false;
    }
}

bool Neuromag::DataWatcher::isWatching()
{
    return m_isWatching;
}

