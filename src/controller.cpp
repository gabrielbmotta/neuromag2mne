
#include "controller.hpp"
#include <unistd.h>


void aaaaa(std::string aa){
};

Controller::Controller()
: mIsActive(false)
{
    m_commandWatcher->registerCallback("test", aaaaa);
    m_commandWatcher->startWatching();
}

void Controller::start()
{
    if(mIsActive)
    {
        std::cout << "Everything is working fine. Move along!\n";
        if(m_commandWatcher->isWatching()){
            m_commandWatcher->stopWatching();
        } else{
            m_commandWatcher->startWatching();
        }

    } else {
        std::cout << "I'm actually going to do some work here.\n";
        mIsActive = true;
    }
}

void printCommand(const std::string& s)
{
    std::cout << s << "\n";
}

