
#include "controller.hpp"
#include <unistd.h>


void testCallback1(void*){
    // friend Controller;
    std::cout << "Aquisition software has been started.\n";
}

void testCallback2(void*){
    std::cout << "Measurement started.\n";
}

Controller::Controller()
: mIsActive(false)
{
    std::cout << "Registering callbacks.\n";
    m_commandWatcher->registerCallback("wkup", testCallback1);
    m_commandWatcher->registerCallback("Acquisition starting", testCallback2);
    m_commandWatcher->showCallbacks();

    //m_commandWatcher->connect();
    //m_commandWatcher->startWatching();
}

void Controller::start()
{
    if(mIsActive)
     {
        //std::cout << "Everything is working fine. Move along!\n";
    } 
    else 
    {
        std::cout << "=== Controller Startup ===\n";
        m_commandWatcher->connect();
        m_commandWatcher->startWatching();
        mIsActive = true;
    }
}

void Controller::printCommand(const std::string& s) const
{
    std::cout << s << "\n";
}

