// DATAWATCHER
#ifndef DATA_WATCHER
#define DATA_WATCHER

#include "types.hpp"
#include "../utils/thread.hpp"
#include "sharedmemorymanager.hpp"
#include "../utils/stringcallbackpair.hpp"

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

    void startWatching();
    void stopWatching();
    bool isWatching();

private:
    std::vector<StringCallbackPair<DataWatcher> >   mCallbacks;
    bool                                mIsWatching;
    Thread                              mThread;
    SharedMemory::Manager               mMemManager;
};
}//namespace
#endif // DATAWATCHER
