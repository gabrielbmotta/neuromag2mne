
#include "controller.hpp"


Controller::Controller()
: mIsActive(false)
{

}

void Controller::start()
{
    if(mIsActive)
    {
        std::cout << "Hello. Everything is working fine. Move along!\n";
    } else {
        std::cout << "I'm actually going to do some work here.\n";
        mIsActive = true;
    }
}

void printCommand(const std::string& s)
{
    std::cout << s << "\n";
}

