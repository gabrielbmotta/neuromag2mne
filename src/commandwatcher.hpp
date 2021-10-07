//commandwatcher.hpp
#ifndef COMMANDWATCHER
#define COMMANDWATCHER

#include "collector_info.hpp"
#include "callback.hpp"
#include "thread.hpp"
#include "socket.hpp"

#include <string>
#include <vector>

void* watchCommands(void*);

class CommandWatcher
{
public:
    typedef Callback<std::string, void (*)(std::string)> CommandCallback;

    enum state{
        DISCONNECTED_NOT_WATCHING,
        CONNECTED_NOT_WATCHING,
        CONNECTED_WATCHING
    };

    CommandWatcher();

    void connect();

    void connect(int, std::string);

    void disconnect();

    void registerCallback(std::string, void (*func)(std::string));

    void deleteCallback(std::string, void (*func)(std::string));

    void showCallbacks();

    void deleteCallback(int);

    void startWatching();

    void stopWatching();

    state getState();

    TCPSocket m_socket;
private:

    std::vector<CommandCallback> m_callbacks;

    state m_state;

    pthread_t m_thread;
};

#endif // COMMANDWATCHER

