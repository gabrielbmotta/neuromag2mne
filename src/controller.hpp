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

    static void measurementAboutToStart(void* ptr)
    {
        Controller* proxy_this = static_cast<Controller*>(ptr);
        proxy_this->mIsActive = true;
    };

private:
    bool configurationIsReady() const;
    void configureCommandWatcherCallbacks();
    void configureDataWatcherCallbacks();
    void configureCommandWatcher();
    void configureDataWatcher();
    void run();

    bool mIsActive;
    bool mContinueRunning;
    bool mOptionsParsed;
    bool mCallbacksConfigured;
    int uSecondsSleepTime;
    ScopedPointer<CommandWatcher> mCommandWatcher;
    ScopedPointer<DataWatcher> mDataWatcher;

    std::queue<SharedPointer<Data> > mDataQueue;
};

#endif // CONTROLLER

