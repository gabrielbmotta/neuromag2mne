#include "datawatcher.hpp"
#include "neuromagshmeminfo.hpp"

#include <iostream>

/*
Enters loop to watch shared memory and call callbacks as data becomes available.

Function to be executed in separate thread by the thread class.
*/
void* Neuromag::watchData(void* input)
{
    DataWatcher* ptr = static_cast<DataWatcher*>(input);
    //mPtr.
    return nullptr;
}

/*
Constructs a DataWatcher
*/
Neuromag::DataWatcher::DataWatcher()
: mIsWatching(false)
{
}

/*
Connects DataWatcher to shared memory.
*/
void Neuromag::DataWatcher::connect()
{
    mMemManager.setParameters(SharedMemory::Parameters::neuromagDefault());
    mMemManager.connect();
}

/*
Disconnects DataWatcher.
*/
void Neuromag::DataWatcher::disconnet()
{
    
}

/*
Adds callbackName to be called when new data is available.
*/
void Neuromag::DataWatcher::registerCallback(void (*func)(void*))
{
    // if(mIsWatching)
    // {
    //     std::cout << "Unable to register callbackName while watching.\n";
    // }
    // else
    // {
    //     mCallbacks.push_back(DataCallback(str, func));
    // }
}
/*
Removes a callbackName.
*/
void Neuromag::DataWatcher::deleteCallback(void (*func)(void*))
{
    
}

/*
Prints all callbacks to screen.
*/
void Neuromag::DataWatcher::showCallbacks()
{
    // int i = 0;
    // std::vector<DataCallback>::iterator it;

    // for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
    // {
    //     std::cout << "(" << i << ") - '" << mCallbacks.at(i).m_trigger << "'\n";
    // }
}

/*
Starts new thread to watch shared memory.
*/
void Neuromag::DataWatcher::startWatching()
{
    if(mThread.startThread(watchData, this))
    {
      mIsWatching = true;
    }
}

/*
Stops watching data.
*/
void Neuromag::DataWatcher::stopWatching()
{
    if(mThread.stopThread())
    {
      mIsWatching = false;
    }
}

/*
Returns whether DataWatcher is watching for commands.
*/
bool Neuromag::DataWatcher::isWatching()
{
    return mIsWatching;
}

