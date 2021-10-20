#include "datawatcher.hpp"
#include "neuromagshmeminfo.hpp"

#include <iostream>

void* Neuromag::watchData(void* input)
{
    DataWatcher* ptr = static_cast<DataWatcher*>(input);
    //ptr.
    return nullptr;
}

Neuromag::DataWatcher::DataWatcher()
: mIsWatching(false)
{
}

void Neuromag::DataWatcher::connect()
{
    mMemManager.setParameters(SharedMemory::Parameters::neuromagDefault());
    mMemManager.connect();
}

void Neuromag::DataWatcher::disconnet()
{
    
}

void Neuromag::DataWatcher::registerCallback(void (*func)(void*))
{
    // if(mIsWatching)
    // {
    //     std::cout << "Unable to register callback while watching.\n";
    // }
    // else
    // {
    //     mCallbacks.push_back(DataCallback(str, func));
    // }
}

void Neuromag::DataWatcher::deleteCallback(void (*func)(void*))
{
    
}

void Neuromag::DataWatcher::deleteCallback(int index)
{
    // if(static_cast<unsigned int>(index) < mCallbacks.size()){
    //     mCallbacks.erase(mCallbacks.begin() + index);
    // }
}

void Neuromag::DataWatcher::showCallbacks()
{
    // int i = 0;
    // std::vector<DataCallback>::iterator it;

    // for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
    // {
    //     std::cout << "(" << i << ") - '" << mCallbacks.at(i).m_trigger << "'\n";
    // }
}

void Neuromag::DataWatcher::startWatching()
{
    if(mThread.startThread(watchData, this))
    {
      mIsWatching = true;
    }
}

void Neuromag::DataWatcher::stopWatching()
{
    if(mThread.stopThread())
    {
      mIsWatching = false;
    }
}

bool Neuromag::DataWatcher::isWatching()
{
    return mIsWatching;
}

