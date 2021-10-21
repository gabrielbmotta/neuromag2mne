#ifndef NEUROMAG2MNE_MULTITHREADQUEUE
#define NEUROMAG2MNE_MULTITHREADQUEUE

#include <queue>
#include "mutex.hpp"
#include <vector>
#include <string>
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

  /*
  Constructs a MultiThreadQueue
  */
  MultiThreadQueue();

  /*
  Returns the element at the front of the queue
  */
  T& front()
  {
    MutexLocker locker(mMutex);
    return mQueue.front();
  };

  /*
  Removes the element at the front of the queue.
  */
  void pop()
  {
    MutexLocker locker(mMutex);
    mQueue.pop();
  };

  /*
  Adds element to queue
  */
  void push(T& item)
  {
    MutexLocker locker(mMutex);
    mQueue.push(item);
  };

  /*
   Returns size of queue
   */
  size_t size()
  {
    MutexLocker locker(mMutex);
    return mQueue.size();
  };

private:
  std::queue<T>   mQueue;
  Mutex           mMutex;
};

#endif //NEUROMAG2MNE_MULTITHREADQUEUE
