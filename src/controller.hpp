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

    Pointer<CommandWatcher> commandWatcher;
    Pointer<DataWatcher> dataWatcher;
};

#endif // CONTROLLER

