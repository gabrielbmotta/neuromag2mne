// DATAWATCHER
#ifndef DATAWATCHER
#define DATAWATCHER

#include "types.hpp"
#include "callback.hpp"
#include <string>
#include <vector>

class DataWatcher
{
public:
    typedef Callback<std::string, void (*)(char*)> DataCallback;

    DataWatcher();

    void startWatching();

    void stopWatching();

    void registerCallback(std::string, void (*func)(char*));

    void deleteCallback(std::string, void (*func)(char*));

    void showCallbacks();

    void deleteCallback(int);

private:
    std::vector<DataCallback> m_callbacks;
};

#endif // DATAWATCHER
