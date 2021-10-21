#ifndef SHARED_MEMORY_MANAGER
#define SHARED_MEMORY_MANAGER

#include <string>
#include "neuromagshmeminfo.hpp"
#include "sharedmemorysocket.hpp"

namespace SharedMemory{

struct Parameters{
    Parameters();
    
    int         mId;
    int         mMaxData;
    int         mNumBlocks;
    std::string mClientPath;
    std::string mServerPath;

    static Parameters neuromagDefault();

private:
    static const int    default_NeuromagClientId;
    static const char*  default_NeuromagClientPath;
    static const char*  default_NeuromagServerPath;
    static const int    default_NeuromagMaxData;
    static const int    default_NeuromagNumBlocks;
};

class Manager
{
public:
    Manager();
    Manager(Parameters param);

    void connect();
    void disconnect();

    void setParameters(const Parameters& param);

    void* getData(); /*will return sharedptr of data once added*/

private:

    bool initSharedMemoryPointer();

    SharedMemory::Socket    mSocket;
    SharedMemory::Block*    mpSharedMemoryBlock;
    Parameters              mParam;
};

}//namespace

#endif
