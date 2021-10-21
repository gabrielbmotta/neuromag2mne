#include "commandwatcher.hpp"
#include "../utils/tcpsocket.hpp"
#include <iostream>
#include <unistd.h>

/*
Enters loop to watch telnet commands and call callbacks as they get triggered.

Function to be executed in separate thread by the thread class.
*/
void* Neuromag::watchCommands(void* receiver)
{
    CommandWatcher* ptr = static_cast<CommandWatcher*>(receiver);
    ptr->mSocket.send(TELNET_CMD_MONI);

    while (true)
    {
        std::string reply = ptr->mSocket.receive_blocking();
        if (reply.size())
        {
            //std::cout << "We've received a message! -- " << reply << "\n";
            ptr->checkForCallbacks(reply);
        }
        
        //ptr->showCallbacks();
        //sleep(1);

    }
    std::cout << "Exiting watch loop.\n";
    
    return nullptr;
}

/*
Constructs a command watcher.
*/
Neuromag::CommandWatcher::CommandWatcher()
: mState(DISCONNECTED_NOT_WATCHING)
{

}

/*
Connects to collector server.
*/
void Neuromag::CommandWatcher::connect()
{
    CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

/*
Connects to collector server at the port and with the password given by parameters.
*/
void Neuromag::CommandWatcher::connect(int port, std::string password)
{
    if(mState != DISCONNECTED_NOT_WATCHING)
    {
        disconnect();
    }

    mSocket.connect(COLLECTOR_ADDR, COLLECTOR_PORT);
//    std::cout << mSocket.receive_blocking() << "\n";
    mSocket.receive_blocking();

//    std::cout << "Sending password...\n";
    mSocket.send(TELNET_CMD_PASS);
//    std::cout << mSocket.receive_blocking() << "\n";
    mSocket.receive_blocking();

//    std::cout << "Sending name...\n";
    mSocket.send(TELNET_CMD_NAME);
//    std::cout << mSocket.receive_blocking() << "\n";
    mSocket.receive_blocking();

  mState = CONNECTED_NOT_WATCHING;
}

/*
Disconnects from server.
*/
void Neuromag::CommandWatcher::disconnect()
{
    if(mState != DISCONNECTED_NOT_WATCHING)
    {
        stopWatching();
        mSocket.disconnect();
      mState = DISCONNECTED_NOT_WATCHING;
    }
}

/*
Adds callback to be called when watching for a specific string in the telnet server.
*/
void Neuromag::CommandWatcher::registerCallback(const std::string& str, void (*func)(void*), void* call)
{
    if(mState == CONNECTED_WATCHING )
    {
        std::cout << "Unable to register callback while watching.\n";
    }
    else 
    {
        mCallbacks.push_back(StringCallbackPair(str, func, call));
    }
}

/*
Removes a callback.
*/
void Neuromag::CommandWatcher::deleteCallback(const std::string& str, void (*func)(void*), void* call)
{
    for (std::vector<StringCallbackPair>::iterator it = mCallbacks.begin();
         it != mCallbacks.end(); ++it)
        {
            if( *it == StringCallbackPair(str,func,call))
            {
                mCallbacks.erase(it);
            }
        }
}

/*
Prints all callbacks to screen.
*/
void Neuromag::CommandWatcher::showCallbacks()
{
    int i = 0;
    std::vector<StringCallbackPair>::iterator it;

    for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
    {
        std::cout << "(" << i << ") - '" << it->trigger_string << " " << it->callback << "'\n";
    }
}

/*
Starts new thread to watch commands.
*/
void Neuromag::CommandWatcher::startWatching()
{
    if(mState == CONNECTED_NOT_WATCHING){
        if(mThread.startThread(watchCommands, this))
        {
          mState = CONNECTED_WATCHING;
        }
    }
}

/*
Stops watching commands.
*/
void Neuromag::CommandWatcher::stopWatching()
{
    if(mState == CONNECTED_WATCHING){
        if (mThread.stopThread())
        {
          mState = CONNECTED_NOT_WATCHING;
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
Neuromag::CommandWatcher::state Neuromag::CommandWatcher::getState()
{
    return mState;
}

/*
Checks for callbacks and call them if applicable.

Parses the input string for the strings in the callbacks. If the callback
string is present, the callback function is called.
*/
void Neuromag::CommandWatcher::checkForCallbacks(std::string msgString)
{
    std::vector<StringCallbackPair>::iterator it;

    for(it = mCallbacks.begin(); it != mCallbacks.end(); it++)
    {
        if(msgString.find(it->trigger_string) != -1){
            std::cout << "We've received a message containing " << it->trigger_string << ".\n";
            it->callback(it->objPtr);
        }
    }
}
