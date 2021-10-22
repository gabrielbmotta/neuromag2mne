#ifndef NEUROMAG2MNE_MUTEX_HPP
#define NEUROMAG2MNE_MUTEX_HPP

#if defined __linux__ || defined __APPLE__
    #include <pthread.h>
#endif

/*
Provides a mutex that can lock and unlock to protect access in multi-threaded contexts.

Recommended usage is to use the MutexLocker and not manually lock/unlock the mutex directly.
*/
class Mutex
{
public:
    Mutex();

    void lock();
    void unlock();

private:
#if defined __linux__ || defined __APPLE__
    pthread_mutex_t mPThreadMutex;
#endif
};

/*
Manages a mutex within its own scope. Attempts to lock on creation and unlock on destruction.
*/
class MutexLocker{
public:
  MutexLocker(Mutex* mutex);
  ~MutexLocker();

private:
  Mutex* mMutex;
};

#endif
