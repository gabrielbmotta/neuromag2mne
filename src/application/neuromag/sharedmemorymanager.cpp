#include "sharedmemorymanager.hpp"

#include <iostream>
#include <sys/shm.h>
#include "application/fiff/fifftag.hpp"

namespace sharedMemory{

//--------------------------------------------------------------------
// Neuromag Shared Memory Defaults.
// Edit these values to change the default hardcoded implementation.
//--------------------------------------------------------------------

const unsigned long int   Parameters::default_NeuromagClientId    = 13014;
const char*               Parameters::default_NeuromagClientPath  = "/neuro/dacq/sockets/dacq_client_";
const char*               Parameters::default_NeuromagServerPath  = "/neuro/dacq/sockets/dacq_server";
const int                 Parameters::default_NeuromagMaxData     = 500 * 1500 * 4;
const int                 Parameters::default_NeuromagNumBlocks   = 100;
const int                 Parameters::default_NeuromagMaxClients  = 10;
}

/*
Constructs a Parameters object with default values.

Values should be set to something valid before use.
*/
sharedMemory::Parameters::Parameters()
    : mId(0)
    , mMaxData(0)
    , mNumBlocks(0)
{
}

/*
Returns a Parameters object initialized to default Neuromag values;
*/
sharedMemory::Parameters sharedMemory::Parameters::neuromagDefault()
{
  sharedMemory::Parameters param;

  param.mId           = sharedMemory::Parameters::default_NeuromagClientId;
  param.mClientPath   = sharedMemory::Parameters::default_NeuromagClientPath;
  param.mServerPath   = sharedMemory::Parameters::default_NeuromagServerPath;
  param.mNumBlocks    = sharedMemory::Parameters::default_NeuromagNumBlocks;
  param.mMaxData      = sharedMemory::Parameters::default_NeuromagMaxData;
  param.mMaxClients   = sharedMemory::Parameters::default_NeuromagMaxClients;

  return param;
}

/*
Constructs a parameterless Manager
*/
sharedMemory::Manager::Manager()
: mParametersConfigured(false)
{
}

/*
Constructs a Manager with the given parameters.
*/
sharedMemory::Manager::Manager(sharedMemory::Parameters param)
: mParametersConfigured(false)
{
  //todo remove this
  if(param.mId == 0)
  {
    std::cout << "mId is zero\n";
  }
}

/*
Connects Manager to shared memory.
*/
void sharedMemory::Manager::connect()
{
  mSocket.connect(static_cast<int>(mParam.mId), mParam.mClientPath);
  initSharedMemoryPointer();
}

void sharedMemory::Manager::connect(const Parameters &param)
{
  setParameters(param);
  connect();
}

/*
Disconnects Manager from shared memory.
*/
void sharedMemory::Manager::disconnect()
{
  mSocket.disconnect();
}

/*
Sets the parameters of this Manager instance.
*/
void sharedMemory::Manager::setParameters(const Parameters& param)
{
  mParam = param;
  mParametersConfigured = true;
}

/*
Gets data from shared memory.
*/
SharedPointer<Data> sharedMemory::Manager::getData()
{
  sharedMemory::Message msg = mSocket.getSharedMemoryMessage();
  SharedPointer<Data> dataPtr;

  char* dataStorage;

  if(msg.size > 0 && msg.shmem_buf > 0)
  {
    sharedMemory::Block* pMemBlock = mpSharedMemoryBlock + msg.shmem_buf;

    dataPtr->tag->kind = msg.kind;
    dataPtr->tag->type = msg.type;
    dataPtr->tag->next = 0;
    dataStorage = new char [msg.size];
    dataPtr->tag->data = static_cast<void*>(dataStorage);
    memcpy(dataPtr->tag->data, pMemBlock->data, static_cast<size_t>(msg.size));

    //std::cout << tag;

    //todo - get data and update client tally to say we read the data
    confirmClientReadData(pMemBlock);
  }

  return dataPtr;
}

/*
Gets pointer to where in the system the block of shared memory is.
*/
void sharedMemory::Manager::initSharedMemoryPointer()
{
  int key = ftok(mParam.mServerPath.c_str(), 'A');
  int id;

  if((id = shmget(key, sizeof(sharedMemory::Block), IPC_CREAT | 0666)) == -1)
  {
    std::cout << "Unable to get shared memory id.\n";
    return;
  }
  if(!(mpSharedMemoryBlock = static_cast<sharedMemory::Block*>(shmat(id, 0, 0))))
  {
    std::cout << "Unable to get shared memory pointer.\n";
    return;
  }
}

/*
Updates section of shared memory that confirms that this client has read this portion of data"
*/
void sharedMemory::Manager::confirmClientReadData(sharedMemory::Block *block)
{
  sharedMemory::Client* pMemClient = block->clients;
  for(int i = 0; i < mParam.mMaxClients; ++i)
  {
    if(pMemClient->id == mParam.mId){
      pMemClient->done = 1;
    }
  }
}
