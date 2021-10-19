//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>

#include "neuromag/commandwatcher.hpp"
#include "neuromag/datawatcher.hpp"
#include "utils/scopedpointer.hpp"

class Controller
{
public:
    Controller();

    void start();

    void stop();

    void printCommand(const std::string& s) const;

    void parseInputArguments(const int argc, char* argv[]);

private:
    bool configurationIsReady() const;
    void configureCallbacks();
    void configureCommandWatcher();
    void run();

    bool mIsActive;
    bool mContinueRunning;
    bool mOptionsParsed;
    bool mCallbacksConfigured;
    int uSecondsSleepTime;
    ScopedPointer<CommandWatcher> m_commandWatcher;
    ScopedPointer<DataWatcher> m_dataWatcher;

};

#endif // CONTROLLER

