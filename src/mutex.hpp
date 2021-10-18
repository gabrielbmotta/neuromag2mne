#ifndef MUTEX
#define MUTEX

#if defined __linux__ || defined __APPLE__
    #include <pthread.h>
#elif defined _WIN32

#endif

class Mutex
{
public:
    Mutex();

private:

#if defined __linux__ || defined __APPLE__
    pthread_mutex_t m_mutex;
#elif defined _WIN32

#endif

};

#endif