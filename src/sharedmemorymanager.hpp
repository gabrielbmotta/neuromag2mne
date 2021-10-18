#ifndef SHAREDMEMORYMANAGER
#define SHAREDMEMORYMANAGER

#include <string>
#include "neuromagshmeminfo.hpp"
#include "sharedmemorysocket.hpp"

class SharedMemoryManager
{
public:
    struct Parameters{
        Parameters(int id, std::string client_path, std::string server_path);
        int m_ID;
        std::string m_client_path;
        std::string m_server_path;
        static Parameters neuromagDefault() {return Parameters(CLIENT_ID, CLIENT_PATH, SERVER_PATH);};
    };

    SharedMemoryManager();
    SharedMemoryManager(Parameters param);

    void connect();
    void disconnect();

    void setParameters(const Parameters& param);

    void* getData(); /*will return sharedptr of data once added*/

private:
    SharedMemorySocket m_socket;

};

#endif