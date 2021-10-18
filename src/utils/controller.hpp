//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>

#include "../neuromag/commandwatcher.hpp"
#include "../neuromag/datawatcher.hpp"
#include "scopedpointer.hpp"

class Controller
{
public:
    Controller();

    void start();

    void printCommand(const std::string& s) const;

private:
    bool mIsActive;

    ScopedPointer<CommandWatcher> m_commandWatcher;
    ScopedPointer<DataWatcher> m_dataWatcher;
};

#endif // CONTROLLER

