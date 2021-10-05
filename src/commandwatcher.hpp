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

    bool isWatching();

private:

    std::vector<CommandCallback> m_callbacks;

    bool m_isWatching;

    pthread_t m_thread;

    TCPSocket m_socket;
};

#endif // COMMANDWATCHER

