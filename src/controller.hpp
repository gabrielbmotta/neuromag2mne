//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <queue>

#include "neuromag/commandwatcher.hpp"
#include "neuromag/datawatcher.hpp"
#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"


//todo super temp do not ship
struct Data{
    int temp;
};

class Controller
{
public:
    Controller();

    void start();

    void stop();

    void printCommand(const std::string& s) const;

    void parseInputArguments(int argc, char* argv[]);

private:
    bool configurationIsReady() const;
    void configureCommandWatcherCallbacks();
    void configureDataWatcherCallbacks();
    void configureCommandWatcher();
    void configureDataWatcher();
    void run();

    inline bool dataAvailable();
    void sendDataToDataManager();

    bool mIsActive;
    bool mAcquisitionSoftwareRunning;
    bool mContinueRunning;
    bool mOptionsParsed;
    bool mCallbacksConfigured;
    int uSecondsSleepTime;
    ScopedPointer<Neuromag::CommandWatcher> mCommandWatcher;
    ScopedPointer<Neuromag::DataWatcher> mDataWatcher;

    std::queue<SharedPointer<Data> > mDataQueue;
};

#endif // CONTROLLER

