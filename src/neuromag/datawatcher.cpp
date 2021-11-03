#include "datawatcher.hpp"
#include "neuromagshmeminfo.hpp"

#include <iostream>
#include <unistd.h>

/*
Enters loop to watch shared memory and call callbacks as data becomes available.

Function to be executed in separate thread by the thread class.
*/
void* neuromag::watchData(void* input)
{
  DataWatcher* pDataWatcher = static_cast<DataWatcher*>(input);
  std::cout << pDataWatcher;
  pDataWatcher->mContinueWatching = true;

  while (pDataWatcher->mContinueWatching)
  {
    SharedPointer<Data> data = pDataWatcher->mMemManager.getData();
    pDataWatcher->sendDataToCallbacks(data);
  }

  return NULL;
}

/*
Constructs a DataWatcher
*/
neuromag::DataWatcher::DataWatcher()
: mContinueWatching(false)
, muSecondsSleep(100)
, mState(DisconnectedNotWatching)
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
void neuromag::DataWatcher::registerCallback(Callback callback)
{
  if(mState == ConnectedWatching)
  {
    std::cout << "Unable to register callbackName while watching.\n";
  }
  else
  {
    mCallbacks.push_back(callback);
  }
}

void neuromag::DataWatcher::registerCallback(void (*function)(SharedPointer<Data>, void* pointer), void* ptr)
{
  mCallbacks.push_back(Callback(function, ptr));
}

/*
Removes a callbackName.
*/
void neuromag::DataWatcher::deleteCallback(Callback)
{

}

void neuromag::DataWatcher::deleteCallback(void (*function)(SharedPointer<Data>, void* pointer), void* ptr)
{
  if(ptr != NULL ) {
    std::cout << "Deleting callback with address: " << function << "\n";
  }
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
  if(mState == ConnectedNotWatching){
    if(mThread.startThread(watchData, this))
    {
      mState = ConnectedWatching;
    }
  }
}

/*
Stops watching data.
*/
void neuromag::DataWatcher::stopWatching()
{
  if(mState == ConnectedWatching){
    mContinueWatching = false;
    usleep(muSecondsSleep);
    if (mThread.stopThread())
    {
      mState = ConnectedNotWatching;
    }
  }
}

/*
Gets the current state of the DataWatcher.

Can be one of the following:
    DisconnectedNotWatching   -   Disconnected. Not watching for data.
    ConnectedNotWatching      -   Connected to shared memory. Not watching for data.
    ConnectedWatching         -   Connected to shared memory. Watching for data.
*/
neuromag::DataWatcher::state neuromag::DataWatcher::getState()
{
  return mState;
}

/*

*/
void neuromag::DataWatcher::sendDataToCallbacks(SharedPointer<Data> data)
{
  for(unsigned long i = 0; i < mCallbacks.size(); ++i)
  {
    mCallbacks[i](data);
  }
}

