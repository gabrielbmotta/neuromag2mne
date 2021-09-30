//commandwatcher.hpp
#ifndef COMMANDWATCHER
#define COMMANDWATCHER

#include <collector_info.hpp>
#include <callback.hpp>
#include <string>
#include <vector>

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


private:
    std::vector<CommandCallback> m_callbacks;
};

#endif // COMMANDWATCHER
