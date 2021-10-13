// DATAWATCHER
#ifndef DATAWATCHER
#define DATAWATCHER

#include "types.hpp"
#include "callback.hpp"
#include "thread.hpp"

#include <string>
#include <vector>

void* watchData(void*);

class DataWatcher
{
public:
    friend void* watchData(void*);

    typedef Callback<std::string, void (*)(char*)> DataCallback;

    DataWatcher();

    void registerCallback(std::string, void (*func)(char*));

    void deleteCallback(std::string, void (*func)(char*));

    void showCallbacks();

    void deleteCallback(int);

    void startWatching();

    void stopWatching();

    bool isWatching();

private:
    std::vector<DataCallback> m_callbacks;

    bool m_isWatching;

    pthread_t m_thread;
};

#endif // DATAWATCHER

