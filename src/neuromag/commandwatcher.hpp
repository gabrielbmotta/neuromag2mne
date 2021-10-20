//commandwatcher.hpp
#ifndef COMMAND_WATCHER
#define COMMAND_WATCHER

#include <string>
#include <vector>

#include "collector_info.hpp"
#include "../utils/thread.hpp"
#include "../utils/tcpsocket.hpp"
#include "stringcallbackpair.h"

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
    void connect(int, std::string);
    void disconnect();

    void registerCallback(const std::string& str, void (*func)(void*), void* receiver);
    void deleteCallback(const std::string& str, void (*func)(void*), void* receiver);
    void showCallbacks();

    void startWatching();
    void stopWatching();
    state getState();

private:
    void checkForCallbacks(std::string);

    std::vector<StringCallbackPair>     mCallbacks;
    state                               mState;
    Thread                              mThread;
    TCPSocket                           mSocket;
};

}//namespace
#endif // COMMANDWATCHER
