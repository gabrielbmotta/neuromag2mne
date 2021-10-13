#include "thread.hpp"

#include <iostream>

Thread::Thread()
: m_isRunning(false)
{

}

bool Thread::startThread(void*(fcn)(void*))
{
#if defined __linux__ || defined __APPLE__
    if(pthread_create(&m_thread, NULL, fcn, this))
    {
        std::cout << "Unable to start CommandWatcehr thread;\n";
        return false;
    }
#elif defined _WIN32

#endif
return false;
}

bool Thread::stopThread()
{
#if defined __linux__ || defined __APPLE__

#elif defined _WIN32

#endif
return false;
}

bool Thread::runAsThread(void*(fcn)(void*))
{
    Thread thread;
    return thread.startThread(fcn);
}