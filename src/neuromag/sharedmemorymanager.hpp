#ifndef NEUROMAG2MNE_SHAREDMEMORYMANAGER_HPP
#define NEUROMAG2MNE_SHAREDMEMORYMANAGER_HPP

#include <string>
#include "neuromagshmeminfo.hpp"
#include "sharedmemorysocket.hpp"

namespace sharedMemory{

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

    void* getData(); /*will return sharedpointer of data once added*/

private:

    bool initSharedMemoryPointer();

    sharedMemory::Socket    mSocket;
    sharedMemory::Block*    mpSharedMemoryBlock;
    Parameters              mParam;
};

}//namespace

#endif
