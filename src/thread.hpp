#ifndef THREADING
#define THREADING

#if defined __linux__ || defined __APPLE__
    #include <pthread.h>
#elif defined _WIN32

#endif

class Thread
{
public:
    Thread();
    bool startThread(void*(fcn)(void*), void* param);
    bool stopThread();

    static bool runAsThread(void*(fcn)(void*), void* param);

private:
    bool m_isRunning;

#if defined __linux__ || defined __APPLE__
    pthread_t m_thread;
#elif defined _WIN32

#endif
    
};

#endif
