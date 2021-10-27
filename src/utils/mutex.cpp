#include "mutex.hpp"

/*
Creates a mutex.
*/
Mutex::Mutex()
{
#if defined __linux__ || defined __APPLE__
  pthread_mutex_init(&mPThreadMutex, NULL);
#endif
}

/*
Attempts to lock the mutex. If already locked, block until mutex can be locked.
*/
void Mutex::lock()
{
#if defined __linux__ || defined __APPLE__
  pthread_mutex_lock(&mPThreadMutex);
#endif
}

/*
Unlocks the mutex.
*/
void Mutex::unlock()
{
#if defined __linux__ || defined __APPLE__
  pthread_mutex_unlock(&mPThreadMutex);
#endif
}

/*
Creates a MutexLocker and locks the mutex that is passed to it.
*/
MutexLocker::MutexLocker(Mutex* mutex)
: mMutex(mutex)
{
  mMutex->lock();
}

/*
Unlocks the managed mutex upon destruction.
*/
MutexLocker::~MutexLocker()
{
  mMutex->unlock();
}

