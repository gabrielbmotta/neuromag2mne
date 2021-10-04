//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>

#include "commandwatcher.hpp"
#include "datawatcher.hpp"
#include "pointer.hpp"

class Controller
{
public:
    Controller();

    void start();

    void printCommand(const std::string& s) const;

private:
    bool mIsActive;

    Pointer<CommandWatcher> m_commandWatcher;
    Pointer<DataWatcher> m_dataWatcher;
};

#endif // CONTROLLER

