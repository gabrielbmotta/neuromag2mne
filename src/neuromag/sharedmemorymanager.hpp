#ifndef SHARED_MEMORY_MANAGER
#define SHARED_MEMORY_MANAGER

#include <string>
#include "neuromagshmeminfo.hpp"
#include "sharedmemorysocket.hpp"

namespace SharedMemory{

struct Parameters{
    Parameters();
    
    int m_ID;
    int m_max_data;
    int m_num_blocks;
    std::string m_client_path;
    std::string m_server_path;

    static Parameters neuromagDefault();

private:
    static const int default_neuromag_client_ID;
    static const char* default_neuromag_client_path;
    static const char* default_neuromag_server_path;
    static const int default_neuromag_max_data;
    static const int default_neuromag_num_blocks;
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

    SharedMemory::Socket m_socket;
    SharedMemory::Block* mpSharedMemoryBlock;
    Parameters m_param;
};

}//namespace

#endif
