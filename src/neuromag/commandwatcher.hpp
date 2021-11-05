//commandwatcher.hpp
#ifndef NEUROMAG2MNE_COMMANDWATCHER_HPP
#define NEUROMAG2MNE_COMMANDWATCHER_HPP

#include <string>
#include <vector>

#include "collector_info.hpp"
#include "../utils/thread.hpp"
#include "../utils/tcpsocket.hpp"
#include "../utils/stringcallbackpair.hpp"
#include "neuromagcontroller.hpp"

namespace neuromag{

void* watchCommands(void*);

class CommandWatcher
{
public:
  friend void* watchCommands(void*);

  struct Callback{
    Callback(std::string trigger,void (*function)(void*, void*), void* pointer)
    : mTriggerString(trigger), mFunction(function), mPointer(pointer){};
    void operator()(void* in){mFunction(in, mPointer);};
    std::string mTriggerString;
    void (*mFunction)(void*, void*);
    void* mPointer;
  };

  enum state{
    DisconnectedNotWatching,
    ConnectedNotWatching,
    ConnectedWatching
  };
  CommandWatcher();
  ~CommandWatcher();

  void connect();
  void connect(unsigned short int port, const std::string& password);
  void disconnect();

  void registerCallback(const Callback& callback);
  void registerCallback(std::string trigger,void (*function)(void*, void*), void* pointer);

  void deleteCallback(const Callback& callback);
  void deleteCallback(std::string trigger,void (*function)(void*, void*), void* pointer);

  void showCallbacks();

  void startWatching();
  void stopWatching();
  state getState();

private:
  void checkForCallbacks(const std::string& msg);

  bool            mContinueWatching;
  unsigned int    muSecondsSleep;
  state           mState;

  std::vector<Callback> mCallbacks;

  Thread        mThread;
  TCPSocket     mSocket;
};

}//namespace
#endif // NEUROMAG2MNE_COMMANDWATCHER_HPP
