//commandwatcher.hpp
#ifndef NEUROMAG2MNE_COMMANDWATCHER_HPP
#define NEUROMAG2MNE_COMMANDWATCHER_HPP

#include <string>
#include <vector>

#include "collector_info.hpp"
#include "../utils/thread.hpp"
#include "../utils/tcpsocket.hpp"
#include "../utils/stringcallbackpair.hpp"
#include "neuromagcontroller.hpp"

namespace neuromag{

void* watchCommands(void*);

class CommandWatcher
{
public:
    friend void* watchCommands(void*);

    enum state{
        DisconnectedNotWatching,
        ConnectedNotWatching,
        ConnectedWatching
    };
    CommandWatcher();
    ~CommandWatcher();

    void connect();
    void connect(unsigned int port, const std::string& password);
    void disconnect();

    void registerCallback(const StringCallbackPair<NeuromagController>& callbackPair);
    void deleteCallback(const StringCallbackPair<NeuromagController>& callbackPair);
    void showCallbacks();

    void startWatching();
    void stopWatching();
    state getState();

private:
    void checkForCallbacks(const std::string& msg);
    bool mContinueWatching;
    unsigned int muSecondsSleep;
    std::vector<StringCallbackPair<NeuromagController> >    mCallbacks;
    state                               mState;
    Thread                              mThread;
    TCPSocket                           mSocket;
};



}//namespace
#endif // NEUROMAG2MNE_COMMANDWATCHER_HPP
