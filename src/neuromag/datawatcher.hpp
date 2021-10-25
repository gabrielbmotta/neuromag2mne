// DATAWATCHER
#ifndef NEUROMAG2MNE_DATAWATCHER_HPP
#define NEUROMAG2MNE_DATAWATCHER_HPP

#include "../utils/thread.hpp"
#include "sharedmemorymanager.hpp"
#include "../utils/stringcallbackpair.hpp"
#include "../utils/sharedpointer.hpp"

#include <string>
#include <vector>

namespace neuromag{

void* watchData(void*);

class DataWatcher
{
public:
    friend void* watchData(void*);

    DataWatcher();
    ~DataWatcher();

    void connect();
    void disconnect();

    void registerCallback(void (*func)(void*));
    void deleteCallback(void (*func)(void*));
    void showCallbacks();

    void startWatching();
    void stopWatching();
    bool isWatching();

private:

    void sendDataToCallbacks(SharedPointer<Data>);
    std::vector<StringCallbackPair<DataWatcher> >   mCallbacks;
    bool                                mIsWatching;
    Thread                              mThread;
    sharedMemory::Manager               mMemManager;
};
}//namespace
#endif // NEUROMAG2MNE_DATAWATCHER_HPP
