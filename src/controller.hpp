//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <queue>

#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"
#include "neuromag/commandwatcher.hpp"
#include "neuromag/datawatcher.hpp"
#include "inputargumentsparser.hpp"
#include "neuromag2mne.hpp"

//todo super temp do not ship
struct Data{
    int temp;
};

class Controller
{
    friend void acquisitionSoftwareRunning(void*);
public:
    Controller();
    void start();
    void stop();
    void parseInputArguments(int argc, char* argv[]);

private:
    void configureCommandWatcherCallbacks();
    void configureDataWatcherCallbacks();
    void configureCommandWatcher();
    void configureDataWatcher();
    static void displayHelp(const std::string& helpStr);
    void run();

    inline bool dataAvailable() const;
    void checkForNewData();

    bool mAcquisitionSoftwareRunning;
    bool mContinueRunning;
    int uSecondsSleepTime;

    bool mVerboseMode;
    bool mRandomDataMode;
    bool mReadFromFileMode;
    std::string mFileNameToRead;

    ScopedPointer<Neuromag::CommandWatcher> mCommandWatcher;
    ScopedPointer<Neuromag::DataWatcher> mDataWatcher;
    ScopedPointer<InputArgumentsParser> mInputArgumentsController;
    std::queue<SharedPointer<Data> > mDataQueue;
};

#endif // CONTROLLER

