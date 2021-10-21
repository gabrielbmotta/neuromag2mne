//commandwatcher.hpp
#ifndef COMMAND_WATCHER
#define COMMAND_WATCHER

#include <string>
#include <vector>

#include "collector_info.hpp"
#include "../utils/thread.hpp"
#include "../utils/tcpsocket.hpp"
#include "../utils/stringcallbackpair.hpp"
#include "neuromagcontroller.hpp"

namespace Neuromag{

void* watchCommands(void*);

class CommandWatcher
{
public:
    friend void* watchCommands(void*);

    enum state{
        DISCONNECTED_NOT_WATCHING,
        CONNECTED_NOT_WATCHING,
        CONNECTED_WATCHING
    };
    CommandWatcher();

    void connect();
    void connect(int port, const std::string& password);
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
    int muSecondsSleep;
    std::vector<StringCallbackPair<NeuromagController> >    mCallbacks;
    state                               mState;
    Thread                              mThread;
    TCPSocket                           mSocket;
};



}//namespace
#endif // COMMANDWATCHER
