
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
  while ( pComWatcher->mContinueWatching )
  {
    std::string reply = pComWatcher->mSocket.receive_blocking();
    if ( reply.size() )
    {
      pComWatcher->checkForCallbacks(reply);
    }
    usleep(pComWatcher->muSecondsSleep);
  }
  std::cout << "Exiting watch loop.\n";

  return nullptr;
}

/*
Constructs a command watcher.
*/
neuromag::CommandWatcher::CommandWatcher()
    : mContinueWatching(false),
      muSecondsSleep(100),
      mState(DisconnectedNotWatching)

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
*/
void neuromag::CommandWatcher::connect(unsigned int port, const std::string& password)
{
  if(mState != DisconnectedNotWatching)
  {
    disconnect();
  }

  mSocket.connect(COLLECTOR_ADDR, port);
//    std::cout << mSocket.receive_blocking() << "\n";
  mSocket.receive_blocking();

//    std::cout << "Sending password...\n";
//todo solve this mess :S
  std::string passwordCMD("pass ");
  passwordCMD.append(password).append(RETURN);

  mSocket.send(passwordCMD.c_str());
//    std::cout << mSocket.receive_blocking() << "\n";
  mSocket.receive_blocking();

//    std::cout << "Sending name...\n";
  mSocket.send(TELNET_CMD_NAME);
//    std::cout << mSocket.receive_blocking() << "\n";
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
Adds callbackName to be called when watching for a specific string in the telnet server.
*/
void neuromag::CommandWatcher::registerCallback(const StringCallbackPair<NeuromagController>& callbackPair)
{
  if(mState == ConnectedWatching )
  {
    std::cout << "Unable to register callbackName while watching.\n";
  }
  else
  {
    mCallbacks.push_back(callbackPair);
  }
}

/*
Removes a callbackName.
*/
void neuromag::CommandWatcher::deleteCallback(const StringCallbackPair<NeuromagController> &callbackPair)
{
  for (std::vector<StringCallbackPair<NeuromagController> >::iterator it = mCallbacks.begin();
       it != mCallbacks.end(); ++it)
  {
    if( *it == callbackPair)
    {
      mCallbacks.erase(it);
    }
  }
}

/*
Prints all callbacks to screen.
*/
void neuromag::CommandWatcher::showCallbacks()
{
  int i = 0;
  std::vector<StringCallbackPair<NeuromagController> >::iterator it;
  for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
  {
    std::cout << "(" << i << ") - '" << it->string() << " " << it->callbackName() << "'\n";
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
    if (mThread.stopThread())
    {
      mState = ConnectedNotWatching;
    }
  }
}

/*
Gets the current state of the CommandWatcher.

Can be one of the following:
    DISCONNECTED_NOT_WATCHING   -   Disconnected. Not watching commands.
    CONNECTED_NOT_WATCHING      -   Connected to server. Not watching commands.
    CONNECTED_WATCHING          -   Connected to server. Watching commands.
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
  std::vector<StringCallbackPair<NeuromagController> >::iterator it;

  for(it = mCallbacks.begin(); it != mCallbacks.end(); it++)
  {
    if( msg.find( it->string() ) != std::string::npos )
    {
      std::cout << "We've received a message containing " << it->string() << ".\n";
      it->callCallback();
    }
  }
}
