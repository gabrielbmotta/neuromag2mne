// DATAWATCHER
#ifndef DATAWATCHER
#define DATAWATCHER

#include "types.hpp"
#include "thread.hpp"
#include "memsocket.hpp"

#include <string>
#include <vector>

void* watchData(void*);

class DataWatcher
{
public:
    friend void* watchData(void*);

    // typedef Callback<std::string, void (*)(char*)> DataCallback;

    DataWatcher();

    void connect();

    void disconnet();

    void registerCallback(void (*func)(void*));

    void deleteCallback(void (*func)(void*));

    void showCallbacks();

    void deleteCallback(int);

    void startWatching();

    void stopWatching();

    bool isWatching();

private:
    // std::vector<DataCallback> m_callbacks;
    std::vector<void(*)(void*)> m_callbacks;

    bool m_isWatching;

    Thread m_thread;
};

#endif // DATAWATCHER

