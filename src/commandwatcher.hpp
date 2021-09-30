//commandwatcher.hpp
#ifndef COMMANDWATCHER
#define COMMANDWATCHER

#include <string>
#include <map>

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

    void deleteCallback(int);

    void startWatching();

    void stopWatching();
<<<<<<< HEAD


    std::map<int, Callback> m_callbackMap;
    int m_callbackCount;
};
=======
};

#endif // COMMANDWATCHER
>>>>>>> c83c6d1fcb8f4f4d4627bd4de4b993b834e15543
