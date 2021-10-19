//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <queue>

#include "neuromag/commandwatcher.hpp"
#include "neuromag/datawatcher.hpp"
#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"


class Controller
{
public:
    Controller();

    void start();

    void stop();

    void printCommand(const std::string& s) const;

    void parseInputArguments( int argc, char* const * argv);

    int getUSecondsSleepTime() const;

    void setUSecondsSleepTime(int uSecondsSleepTime);

private:
    bool configurationIsReady() const;
    void configureCallbacks();
    void configureCommandWatcher();
    void run();

    bool mIsActive;
    bool mContinueRunning;
    bool mOptionsParsed;
    bool mCallbacksConfigured;
    int mUSecondsSleepTime;

    bool mMeasurementStarted;
public:
    bool isMMeasurementStarted() const;

    void setMMeasurementStarted(bool mMeasurementStarted);

    void measurementHasStarted(void*); // 0xaffff04 void func();

    void pushNewData(SharedPointer<DataChunk> data);

    void incrementCount();

private:

    std:queue<SharedPointer<DataChunk> > mData;
    ScopedPointer<CommandWatcher> mCommandWatcher;
    ScopedPointer<DataWatcher> mDataWatcher;
};

#endif // CONTROLLER

