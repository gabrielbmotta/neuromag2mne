//commandwatcher.hpp
#ifndef COMMANDWATCHER
#define COMMANDWATCHER

#include "collector_info.hpp"
// #include "callback.hpp"
#include "../utils/thread.hpp"
#include "../utils/tcpsocket.hpp"

#include <string>
#include <vector>

void* watchCommands(void*);

class CommandWatcher
{
public:
    friend void* watchCommands(void*);
    // typedef Callback<std::string, void (*)(std::string)> CommandCallback;

    enum state{
        DISCONNECTED_NOT_WATCHING,
        CONNECTED_NOT_WATCHING,
        CONNECTED_WATCHING
    };

    CommandWatcher();

    void connect();

    void connect(int, std::string);

    void disconnect();

    void registerCallback(std::string, void (*func)(void*));

    void deleteCallback(std::string, void (*func)(void*));

    void showCallbacks();

    void startWatching();

    void stopWatching();

    state getState();

    void checkForCallbacks(std::string);

private:
    struct stringCallbackPair
    {
        stringCallbackPair(std::string s, void(*fcn)(void*)){trigger_string = s;callback = fcn;};
        std::string trigger_string;
        void(* callback)(void*);
        bool operator==(const stringCallbackPair& other)
        {return (trigger_string == other.trigger_string) && (callback == other.callback);}
    };

    std::vector<stringCallbackPair> m_callbacks;

    state m_state;

    Thread m_thread;

    TCPSocket m_socket;
};

#endif // COMMANDWATCHER

