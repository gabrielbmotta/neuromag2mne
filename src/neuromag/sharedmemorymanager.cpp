#include "sharedmemorymanager.hpp"
#include <iostream>
#include <sys/shm.h>


namespace SharedMemory{

//--------------------------------------------------------------------
// Neuromag Shared Memory Defaults.
// Edit these values to change the default hardcoded implementation.
//--------------------------------------------------------------------

const int   Parameters::default_NeuromagClientId    = 1304;
const char* Parameters::default_NeuromagClientPath  = "/neuro/dacq/sockets/dacq_client_";
const char* Parameters::default_NeuromagServerPath  = "/neuro/dacq/sockets/dacq_server";
const int   Parameters::default_NeuromagMaxData     = 500 * 1500 * 4;
const int   Parameters::default_NeuromagNumBlocks   = 100;
}

/*
Constructs a Parameters object with default values.

Values should be set to something valid before use.
*/
SharedMemory::Parameters::Parameters()
: mId(0)
, mClientPath("")
, mServerPath("")
, mNumBlocks(0)
, mMaxData(0)
{
}

/*
Returns a Parameters object initialized to default Neuromag values;
*/
SharedMemory::Parameters SharedMemory::Parameters::neuromagDefault()
{
    SharedMemory::Parameters param;

    param.mId           = SharedMemory::Parameters::default_NeuromagClientId;
    param.mClientPath   = SharedMemory::Parameters::default_NeuromagClientPath;
    param.mServerPath   = SharedMemory::Parameters::default_NeuromagServerPath;
    param.mNumBlocks    = SharedMemory::Parameters::default_NeuromagNumBlocks;
    param.mMaxData      = SharedMemory::Parameters::default_NeuromagMaxData;

    return param;
}

/*
Constructs a parameterless Manager
*/
SharedMemory::Manager::Manager()
{
}

/*
Constructs a Manager with the given parameters.
*/
SharedMemory::Manager::Manager(SharedMemory::Parameters param)
: mParam(param)
{
}

/*
Connects Manager to shared memory.
*/
void SharedMemory::Manager::connect()
{
    mSocket.connect(mParam.mId, mParam.mClientPath);

}

/*
Disconnects Manager from shared memory.
*/
void SharedMemory::Manager::disconnect()
{

}

/*
Sets the parameters of this Manager instance.
*/
void SharedMemory::Manager::setParameters(const Parameters& param)
{
    mParam = param;
}

/*
Gets data from shared memory.
*/
void* SharedMemory::Manager::getData()
{
    SharedMemory::Block* pMemBlock = NULL;
    SharedMemory::Client* pMemClient = NULL;
    SharedMemory::Message msg = mSocket.getSharedMemoryMessage();

    if(msg.size > 0 && msg.shmem_buf >= 0)
    {
        pMemBlock = mpSharedMemoryBlock + msg.shmem_buf;
        pMemClient = pMemBlock->clients;

        //todo - get data and update client tally to say we read the data
    }

    return NULL;
}

/*
Gets pointer to where in the system the block of shared memory is.
*/
bool SharedMemory::Manager::initSharedMemoryPointer()
{
    pthread_key_t key = ftok(mParam.mServerPath.c_str(), 'A');

    int id;
    if((id = shmget(key, sizeof(SharedMemory::Block), IPC_CREAT | 0666)) == -1)
    {
        std::cout << "Unable to get shared memory id.\n";
        return false;
    }
    if(!(mpSharedMemoryBlock = static_cast<SharedMemory::Block*>(shmat(id,0,0))))
    {
        std::cout << "Unable to get shared memory pointer.\n";
        return false;
    }

    return true;
}
