#include <iostream>
#include <unistd.h>

#include "commandwatcher.hpp"
#include "../utils/tcpsocket.hpp"

/*
Enters loop to watch telnet commands and call callbacks as they get triggered.

Function to be executed in separate thread by the thread class.
*/
void* neuromag::watchCommands(void* receiver)
{
  CommandWatcher* pComWatcher = static_cast<CommandWatcher*>(receiver);
  pComWatcher->mSocket.send(TELNET_CMD_MONI);
  pComWatcher->mContinueWatching = true;

  while (pComWatcher->mContinueWatching)
  {
    std::string reply = pComWatcher->mSocket.receive_blocking();
    if (reply.size())
    {
      pComWatcher->checkForCallbacks(reply);
    }

    usleep(pComWatcher->muSecondsSleep);
  }
  std::cout << "Exiting watch loop.\n";

  return NULL;
}

/*
Constructs a command watcher.
*/
neuromag::CommandWatcher::CommandWatcher()
: mContinueWatching(false)
, muSecondsSleep(100)
, mState(DisconnectedNotWatching)
{
}

neuromag::CommandWatcher::~CommandWatcher()
{

}

/*
Connects to collector server.
*/
void neuromag::CommandWatcher::connect()
{
  CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

/*
Connects to collector server at the port and with the password given by parameters.

Does nothing if already connected to something.
*/
void neuromag::CommandWatcher::connect(unsigned short int port, const std::string& password)
{
  std::cout << password;
  if(mState != DisconnectedNotWatching)
  {
    return;
  }

  mSocket.connect(COLLECTOR_ADDR, port);
  mSocket.receive_blocking();

  mSocket.send(TELNET_CMD_PASS);
  mSocket.receive_blocking();

  mSocket.send(TELNET_CMD_NAME);
  mSocket.receive_blocking();

  mState = ConnectedNotWatching;
}

/*
Disconnects from server.
*/
void neuromag::CommandWatcher::disconnect()
{
  if(mState != DisconnectedNotWatching)
  {
    stopWatching();
    mSocket.disconnect();
    mState = DisconnectedNotWatching;
  }
}

/*
Adds callback to be called when watching for a specific string in the telnet server.
*/
void neuromag::CommandWatcher::registerCallback(const Callback& callback)
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

void neuromag::CommandWatcher::registerCallback(std::string trigger,void (*function)(void*, void*), void* pointer)
{
  mCallbacks.push_back(Callback(trigger, function, pointer));
}

/*
Removes a callback.
*/
void neuromag::CommandWatcher::deleteCallback(const Callback& callback)
{
 std::cout << "Deleting callback: " << callback.mTriggerString << "\n";
}

void neuromag::CommandWatcher::deleteCallback(std::string trigger,void (*function)(void*, void*), void* pointer)
{
 std::cout << "Deleting callback: " << trigger << " with address: " << function << "\n";
  (void)pointer;
}

/*
Prints all callbacks to screen.
*/
void neuromag::CommandWatcher::showCallbacks()
{
  int i = 0;
  std::vector<Callback>::iterator it;
  for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
  {
    std::cout << "(" << i << ") - '" << it->mTriggerString << "'\n";
  }
}

/*
Starts new thread to watch commands.
*/
void neuromag::CommandWatcher::startWatching()
{
  if(mState == ConnectedNotWatching){
    if(mThread.startThread(watchCommands, this))
    {
      mState = ConnectedWatching;
    }
  }
}

/*
Stops watching commands.
*/
void neuromag::CommandWatcher::stopWatching()
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
Gets the current state of the CommandWatcher.

Can be one of the following:
    DisconnectedNotWatching   -   Disconnected. Not watching commands.
    ConnectedNotWatching      -   Connected to server. Not watching commands.
    ConnectedWatching         -   Connected to server. Watching commands.
*/
neuromag::CommandWatcher::state neuromag::CommandWatcher::getState()
{
  return mState;
}

/*
Checks for callbacks and call them if applicable.

Parses the input string for the strings in the callbacks. If the callback
string is present, the callback function is called.
*/
void neuromag::CommandWatcher::checkForCallbacks(const std::string& msg)
{
  for(size_t i = 0; i < mCallbacks.size(); ++i)
  {
    if(msg.find(mCallbacks[i].mTriggerString) != std::string::npos)
    {
      std::cout << "We've received a message containing " << mCallbacks[i].mTriggerString << ".\n";
      mCallbacks[i](NULL);
    }
  }
}
