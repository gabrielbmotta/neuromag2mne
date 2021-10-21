//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <queue>

#include "neuromag2mne.hpp"
#include "utils/scopedpointer.hpp"
#include "inputargumentsparser.hpp"

//todo super temp do not ship
struct Data{
    int temp;
};

class Controller
{
    friend void stopCallback(void*);
public:
    Controller();
    void start();
    void stop();
    void parseInputArguments(int argc, char* argv[]);

private:
    void run();
    static void displayHelp(const std::string& helpStr);

    inline bool dataAvailable() const;
    void checkForNewData();

    void configureNeuromagController();
    void configureRandomDataController();
    void configureFileReaderController();
    void configureFileWriterController();
    void configureDataSenderController();
    void sendData();
    void prepareToExitApplication();


    bool mContinueRunning;
    int uSecondsSleepTime;
    bool mVerboseMode;

    bool mNeuromagMode;
    bool mRandomDataMode;
    bool mReadFromFileMode;
    std::string mFileNameToRead;
    bool mSendDataMode;
    bool mSaveToFileMode;
    std::string mFileNameToSave;

    ScopedPointer<InputArgumentsParser> mInputArgumentsController;
    ScopedPointer<Neuromag::NeuromagController> mNeuromagController;
    ScopedPointer<RandomDataController> mRandomDataController;
    ScopedPointer<FileController> mFileReaderController;

    ScopedPointer<DataSenderController> mDataSenderController;
    ScopedPointer<FileController> mFileWriterController;

    std::queue<SharedPointer<Data> > mDataQueue;
};

#endif // CONTROLLER

