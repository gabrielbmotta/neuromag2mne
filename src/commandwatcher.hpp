//commandwatcher.hpp
#ifndef COMMANDWATCHER
#define COMMANDWATCHER

#include <string>
#include <vector>

struct Callback{
    Callback(std::string str, void (*func)(std::string))
    : command(str)
    , function(func)
    { };

    std::string command;
    void (*function)(std::string);
};

class CommandWatcher
{
public:
    CommandWatcher();

    void connect();

    void disconnect();

    void registerCallback(std::string, void (*func)(std::string));

    void deleteCallback(std::string, void (*func)(std::string));

    void showCallbacks();

    void deleteCallback(int);

    void startWatching();

    void stopWatching();

    std::vector<Callback> m_callbacks;
    int m_callbackCount;
};

#endif // COMMANDWATCHER
