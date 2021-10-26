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

  struct Callback{
    Callback(void (*function)(SharedPointer<Data>, void* pointer), void* pointer)
    : mFunction(function), mPointer(pointer){};
    void operator()(SharedPointer<Data> in){mFunction(in, mPointer);};
    void (*mFunction)(SharedPointer<Data>, void* pointer);
    void* mPointer;
  };

  enum state{
    DisconnectedNotWatching,
    ConnectedNotWatching,
    ConnectedWatching
  };

  DataWatcher();
  ~DataWatcher();

  void connect();
  void disconnect();

  void registerCallback(Callback);
  void registerCallback(void (*function)(SharedPointer<Data>, void* pointer), void*);

  void deleteCallback(Callback);
  void deleteCallback(void (*function)(SharedPointer<Data>, void* pointer), void*);

  void showCallbacks();

  void startWatching();
  void stopWatching();
  state getState();

private:
  void sendDataToCallbacks(SharedPointer<Data>);

  bool            mContinueWatching;
  unsigned int    muSecondsSleep;
  state           mState;

  std::vector<Callback> mCallbacks;

  Thread                  mThread;
  sharedMemory::Manager   mMemManager;
};
}//namespace
#endif // NEUROMAG2MNE_DATAWATCHER_HPP
