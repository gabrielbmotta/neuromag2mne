#include "sharedmemorymanager.hpp"

//--------------------------------------------------------------------
// Neuromag Shared Memory Defaults.
// 
// Edit these values to change the default hardcoded implementation.
//--------------------------------------------------------------------

namespace SharedMemory{
const int   Parameters::default_neuromag_client_ID =      1304;
const char* Parameters::default_neuromag_client_path =    "/neuro/dacq/sockets/dacq_client_";
const char* Parameters::default_neuromag_server_path =    "/neuro/dacq/sockets/dacq_server";
const int   Parameters::default_neuromag_max_data =       500*1500*4;
const int   Parameters::default_neuromag_num_blocks =     100;
}
//--------------------------------------------------------------------
// Implementation
//--------------------------------------------------------------------

SharedMemory::Parameters::Parameters()
: m_ID(0)
, m_client_path("")
, m_server_path("")
, m_num_blocks(0)
, m_max_data(0)
{
}

SharedMemory::Parameters SharedMemory::Parameters::neuromagDefault()
{
    SharedMemory::Parameters param;

    param.m_ID = SharedMemory::Parameters::default_neuromag_client_ID;
    param.m_client_path = SharedMemory::Parameters::default_neuromag_client_path;
    param.m_server_path = SharedMemory::Parameters::default_neuromag_server_path;
    param.m_num_blocks = SharedMemory::Parameters::default_neuromag_num_blocks;
    param.m_max_data = SharedMemory::Parameters::default_neuromag_max_data;

    return param;
}

SharedMemory::Manager::Manager()
{

}

SharedMemory::Manager::Manager(SharedMemory::Parameters param)
{

}

void SharedMemory::Manager::connect()
{
    m_socket.connect(m_param.m_ID, m_param.m_client_path, m_param.m_server_path);
}

void SharedMemory::Manager::disconnect()
{

}

void SharedMemory::Manager::setParameters(const Parameters& param)
{
    m_param = param;
}

void* SharedMemory::Manager::getData() /*will return sharedptr of data once added*/
{
    return NULL;
}
