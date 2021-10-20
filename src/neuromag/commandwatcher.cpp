#include "commandwatcher.hpp"
#include "../utils/tcpsocket.hpp"
#include <iostream>
#include <unistd.h>

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

Neuromag::CommandWatcher::CommandWatcher()
: mState(DISCONNECTED_NOT_WATCHING)
{

}

void Neuromag::CommandWatcher::connect()
{
    CommandWatcher::connect(COLLECTOR_PORT, COLLECTOR_PASS);
}

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

void Neuromag::CommandWatcher::disconnect()
{
    if(mState != DISCONNECTED_NOT_WATCHING)
    {
        stopWatching();
        mSocket.disconnect();
      mState = DISCONNECTED_NOT_WATCHING;
    }
}

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

void Neuromag::CommandWatcher::showCallbacks()
{
    int i = 0;
    std::vector<StringCallbackPair>::iterator it;

    for(it = mCallbacks.begin(); it != mCallbacks.end(); it++, i++)
    {
        std::cout << "(" << i << ") - '" << it->trigger_string << " " << it->callback << "'\n";
    }
}

void Neuromag::CommandWatcher::startWatching()
{
    if(mState == CONNECTED_NOT_WATCHING){
        if(mThread.startThread(watchCommands, this))
        {
          mState = CONNECTED_WATCHING;
        }
    }
}

void Neuromag::CommandWatcher::stopWatching()
{
    if(mState == CONNECTED_WATCHING){
        if (mThread.stopThread())
        {
          mState = CONNECTED_NOT_WATCHING;
        }
    }
}

Neuromag::CommandWatcher::state Neuromag::CommandWatcher::getState()
{
    return mState;
}

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
