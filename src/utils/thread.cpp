#include "thread.hpp"

#include <iostream>

Thread::Thread()
        : mIsRunning(false)
{

}

bool Thread::startThread(void*(fcn)(void*), void* param)
{
#if defined __linux__ || defined __APPLE__
  if(pthread_create(&mThread, NULL, fcn, param))
  {
    std::cout << "Unable to start thread;\n";
    return false;
  }
#elif defined _WIN32

#endif
  mIsRunning = true;
  return true;
}

bool Thread::stopThread()
{
#if defined __linux__ || defined __APPLE__
  if (pthread_cancel(mThread))
  {
    std::cout << "Unable to stop thread;\n";
    return false;
  }
  return true;
#elif defined _WIN32

#endif
  mIsRunning = false;
  return false;
}

bool Thread::runAsThread(void*(fcn)(void*), void* param)
{
  Thread thread;
  return thread.startThread(fcn, param);
}
