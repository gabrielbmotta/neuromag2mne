
#include "controller.hpp"
#include <unistd.h>


void testCallback(std::string aa){
    // friend Controller;

}

Controller::Controller()
: mIsActive(false)
{
    m_commandWatcher->registerCallback("test", testCallback);
    m_commandWatcher->startWatching();
}

void Controller::start()
{
    if(mIsActive)
    {
        std::cout << "Everything is working fine. Move along!\n";
    } 
    else 
    {
        std::cout << "I'm actually going to do some work here.\n";
        mIsActive = true;
    }
}

void Controller::printCommand(const std::string& s) const
{
    std::cout << s << "\n";
}

