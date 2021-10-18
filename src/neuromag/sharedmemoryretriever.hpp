#ifndef SHARED_MEMORY_RETRIEVER
#define SHARED_MEMORY_RETRIEVER

namespace SharedMemory{

class Retriever
{
public:
    Retriever();
    void setSharedMemoryLocation();

    void* getData();
};


}//namespace
#endif