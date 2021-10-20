// DATAWATCHER
#ifndef DATAWATCHER
#define DATAWATCHER

#include "types.hpp"
#include "../utils/thread.hpp"
#include "sharedmemorymanager.hpp"
#include "stringcallbackpair.h"

#include <string>
#include <vector>

namespace Neuromag{

void* watchData(void*);

class DataWatcher
{
public:
    friend void* watchData(void*);

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
    std::vector<StringCallbackPair> mCallbacks;
    bool mIsWatching;
    Thread mThread;
    SharedMemory::Manager mMemManager;
};

}
#endif // DATAWATCHER

