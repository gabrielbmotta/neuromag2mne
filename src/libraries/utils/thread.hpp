#ifndef THREADING
#define THREADING

#include "utils_global.hpp"

#if defined __linux__ || defined __APPLE__
    #include <pthread.h>
#elif defined _WIN32

#endif

class Thread
{
public:
    Thread();
    ~Thread();
    bool startThread(void*(fcn)(void*), void* param);
    bool stopThread();

    static bool runAsThread(void*(fcn)(void*), void* param);

private:
    bool mIsRunning;

#if defined __linux__ || defined __APPLE__
    pthread_t mThread;
#elif defined _WIN32

#endif
    
};

#endif
