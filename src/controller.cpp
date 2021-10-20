
#include "controller.hpp"
#include <unistd.h>

void acquisitionSoftwareRunning(void* ptr)
{
    std::cout << "Acquisition software has been started.\n";
    Controller* c(static_cast<Controller*>(ptr));
    c->mAcquisitionSoftwareRunning = true;
}

// =========================================================================

Controller::Controller()
: mAcquisitionSoftwareRunning(false),
  mContinueRunning(false),
  uSecondsSleepTime(100)
{

}

void Controller::start()
{
  std::cout << "=== Controller Startup ===\n";
  configureCommandWatcher();
  //todo figure out play between dependent controllers.
  run();
}

void Controller::configureCommandWatcher()
{
  configureCommandWatcherCallbacks();
  mCommandWatcher->connect();
  mCommandWatcher->startWatching();
}

void Controller::configureCommandWatcherCallbacks()
{
  std::cout << "Registering CommandWatcher callbacks.\n";

  mCommandWatcher->registerCallback("wkup", acquisitionSoftwareRunning, this);
  mCommandWatcher->showCallbacks();
}

void Controller::configureDataWatcher()
{
    configureCommandWatcherCallbacks();
    mDataWatcher->connect();
    mDataWatcher->startWatching();
}

void Controller::configureDataWatcherCallbacks()
{
//  std::cout << "Registering DataWatcher callbacks.\n";
//  mDataWatcher->registerCallback("xxx", testCallback1, this);
}

void Controller::run()
{
  mContinueRunning = true;
  while (mContinueRunning)
  {
    if(mAcquisitionSoftwareRunning)
    {
      configureDataWatcher();
      sendDataToDataManager();
    }
    usleep(uSecondsSleepTime);
  }
}

void Controller::sendDataToDataManager()
{
  while(mAcquisitionSoftwareRunning)
  {
    if( dataAvailable() ){
      SharedPointer<Data> data = mDataQueue.front();
      mDataQueue.pop();
      //todo - put 'data' somewhere.
    }
  }

}

void Controller::stop()
{
  mContinueRunning = false;
}

void Controller::parseInputArguments(const int argc, char* argv[])
{
  OptionsPack parsingResult = mInputArgumentsController->parse(argc, argv);
  if ( mInputArgumentsController->errorWhileParsingOptions() )
  {
    std::cout << "\nSomething went wrong parsing commandline input options.\n";
    displayHelp(mInputArgumentsController->getHelp());
    exit(1);
  }

  if ( parsingResult.displayHelp )
  {
    displayHelp(mInputArgumentsController->getHelp());
    exit(0);
  } else {
    mVerboseMode = parsingResult.verboseMode;
    mRandomDataMode = parsingResult.randomDataMode;
    mReadFromFileMode = parsingResult.readFromFileMode;
    if(mReadFromFileMode )
    {
      mFileNameToRead = parsingResult.fileNameToRead;
    }
  }
}

bool Controller::dataAvailable() const
{
  return !mDataQueue.empty();
}

void Controller::displayHelp(const std::string& helpString)
{
  //todo preamble name date etc...
  std::cout << "====\n";
  std::cout << " Neuromag2MNE\n";
  std::cout << " Version. " << versionMayor << "." << versionMinor << "\n";
  std::cout << helpString;
  std::cout << "\n";
  //todo postambleß
}