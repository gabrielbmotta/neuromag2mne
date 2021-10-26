#ifndef NEUROMAG2MNE_MULTITHREADQUEUE
#define NEUROMAG2MNE_MULTITHREADQUEUE

#include <queue>
#include "mutex.hpp"
#include <vector>
#include <string>
#include "utils_global.hpp"

template<typename T>
/*
Provides a queue that can be used across threads.

This just ensures that there are not multiple push/pop operations
being performed at the same time. It does not fix the undefined
behavior of accessing an empty stl container. This class is to
facilitate pushing from separate threads, another layer of security
is needed if multiple 'users' are going to be popping data.
*/
class MultiThreadQueue {
public:

  class Item{
  public:
    bool valid() {return mValid;};
    T& data() {return mData;};
  private:
    Item(bool valid, T& data):mValid(valid),mData(data){};
    Item(){};

    bool mValid;
    T& mData;
  };

  /*
  Constructs a MultiThreadQueue
  */
  MultiThreadQueue(){};

  /*
  Returns the element at the front of the queue
  */
  T& front()
  {
    MutexLocker locker(&mMutex);
    return mQueue.front();
  };

//todo -  decide if we want this class to be multi-reader (popper) safe
//        as well as thread safe. I(Gabriel) don't think it's necessary
//        for what we are going to use this class for.
//  Item front()
//  {
//    MutexLocker locker(mMutex);
//    if(mQueue.size() > 0)
//    {
//      return Item(true, mQueue.front());
//    }
//    else
//    {
//      return Item(true, mQueue.front());
//    }
//  };
//  void pop()
//  {
//    MutexLocker locker(mMutex);
//    if(mQueue.size() > 0)
//    {
//      mQueue.pop();
//    }
//  };

  /*
  Removes the element at the front of the queue.
  */
  void pop()
  {
    MutexLocker locker(&mMutex);
    mQueue.pop();
  };

  /*
  Adds element to queue
  */
  void push(T& item)
  {
    MutexLocker locker(&mMutex);
    mQueue.push(item);
  };

  /*
   Returns size of queue
   */
  size_t size()
  {
    MutexLocker locker(&mMutex);
    return mQueue.size();
  };

  bool empty()
  {
    MutexLocker locker(&mMutex);
    return !mQueue.size();
  }

private:
  std::queue<T>   mQueue;
  Mutex           mMutex;
};

#endif //NEUROMAG2MNE_MULTITHREADQUEUE
