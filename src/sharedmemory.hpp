#ifndef SHAREDMEMORY
#define SHAREDMEMORY

#include "memsocket.hpp"

class SharedMemory
{
public:
    SharedMemory();

private:
    SharedMemorySocket m_socket;

};

#endif