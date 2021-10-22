#include "datawatcher.hpp"
#include "neuromagshmeminfo.hpp"

#include <iostream>

/*
Enters loop to watch shared memory and call callbacks as data becomes available.

Function to be executed in separate thread by the thread class.
*/
void* neuromag::watchData(void* input)
{
    DataWatcher* ptr = static_cast<DataWatcher*>(input);
    std::cout << ptr;
    //mPtr.
    return nullptr;
}

/*
Constructs a DataWatcher
*/
neuromag::DataWatcher::DataWatcher()
: mIsWatching(false)
{
}

neuromag::DataWatcher::~DataWatcher()
{

}

/*
Connects DataWatcher to shared memory.
*/
void neuromag::DataWatcher::connect()
{
    mMemManager.setParameters(sharedMemory::Parameters::neuromagDefault());
    mMemManager.connect();
}

/*
Disconnects DataWatcher.
*/
void neuromag::DataWatcher::disconnect()
{
    
}

/*
Adds callbackName to be called when new data is available.
*/
void neuromag::DataWatcher::registerCallback(void (*func)(void*))
{
  std::cout << func;
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
void neuromag::DataWatcher::deleteCallback(void (*func)(void*))
{
    std::cout << func;
}

/*
Prints all callbacks to screen.
*/
void neuromag::DataWatcher::showCallbacks()
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
void neuromag::DataWatcher::startWatching()
{
    if(mThread.startThread(watchData, this))
    {
      mIsWatching = true;
    }
}

/*
Stops watching data.
*/
void neuromag::DataWatcher::stopWatching()
{
    if(mThread.stopThread())
    {
      mIsWatching = false;
    }
}

/*
Returns whether DataWatcher is watching for commands.
*/
bool neuromag::DataWatcher::isWatching()
{
    return mIsWatching;
}

