//commandwatcher.hpp
#ifndef COMANDWATCHER
#define COMMANDWATCHER

#include <string>

class CommandWatcher
{
public:
    CommandWatcher();

    void connect();

    void disconnect();

    void registerCallback(std::string, void (*func)(std::string));

    void deleteCallback(std::string, void (*func)(std::string));

    void deleteCallback(int);

    void startWatching();

    void stopWatching();
};

#endif // COMMANDWATCHER
