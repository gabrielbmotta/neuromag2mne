
#include <unistd.h>
#include "controller.hpp"
#include "utils/sharedpointer.hpp"


void stopCallback(void* ptr)
{
  Controller* cPtr(static_cast<Controller*>(ptr));
  cPtr->stop();
}

Controller::Controller()
    : mContinueRunning(false),
      uSecondsSleepTime(100),
      mVerboseMode(false),
      mNeuromagMode(false),
      mRandomDataMode(false),
      mReadFromFileMode(false),
      mSendDataMode(false),
      mSaveToFileMode(false)
{

}

void Controller::start()
{
  std::cout << "=== Controller Startup ===\n";
  if( mNeuromagMode ) {
    configureNeuromagController();
  } else if( mRandomDataMode ) {
    configureRandomDataController();
  } else if( mReadFromFileMode ) {
    configureFileReaderController();
  }

  if( mSaveToFileMode )
  {
    configureFileWriterController();
  }
  if ( mSendDataMode )
  {
    configureDataSenderController();
  }

  run();
}

void Controller::run()
{
  mContinueRunning = true;
  while (mContinueRunning)
  {
    checkForNewData();
    usleep(uSecondsSleepTime);
  }
  prepareToExitApplication();
}

void Controller::checkForNewData()
{
  if( dataAvailable() )
  {
    sendData();
  }
}

void Controller::sendData()
{
  while ( dataAvailable() )
  {
    //todo be careful make read from queue multithread safe!!!
    if ( mSaveToFileMode )
    {
      mFileWriterController->pushNewData(mDataQueue.front());
    }
    if ( mSendDataMode )
    {
      mDataSenderController->pushNewData(mDataQueue.front());
    }
    mDataQueue.pop();
  }
}

bool Controller::dataAvailable() const
{
  return !mDataQueue.empty();
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
    std::cout << "Something went wrong parsing commandline input options.\n";
    displayHelp(mInputArgumentsController->getHelpStr());
    exit(1);
  }
  if ( parsingResult.displayHelp )
  {
    displayHelp(mInputArgumentsController->getHelpStr());
    exit(0);
  } else {
    mVerboseMode = parsingResult.verboseMode;
    mRandomDataMode = parsingResult.randomDataMode;
    mReadFromFileMode = parsingResult.readFromFileMode;
    //todo add an enum to store the Source Mode instead of independent bools.
    if( mReadFromFileMode )
    {
      mFileNameToRead = parsingResult.fileNameToRead;
    }
  }
}

void Controller::displayHelp(const std::string& helpString)
{
  //todo preamble name date etc...
  std::cout << "\n";
  std::cout << "Neuromag2MNE\n";
  std::cout << "Version. " << versionMayor << "." << versionMinor << "\n";
  std::cout << helpString;
  std::cout << "\n";
  //todo postamble
}

void Controller::prepareToExitApplication()
{
  if( mNeuromagMode ) {
    mNeuromagController->stop();
  } else if( mRandomDataMode ) {
    mRandomDataController->stop();
  } else if( mReadFromFileMode ) {
    mFileReaderController->stop();
  }

  if( mSaveToFileMode )
  {
    mFileWriterController->stop();
  }
  if ( mSendDataMode )
  {
    mDataSenderController->stop();
  }
}

void Controller::configureNeuromagController()
{
  //todo figure out how to report configuration options...
  mNeuromagController->start();
}

void Controller::configureRandomDataController()
{
  //todo figure out how to report configuration options...
//  specify random generation algorithm.
  mRandomDataController->start();
}

void Controller::configureFileReaderController()
{
  //todo figure out how to report configuration options...
  //set the name of the file to read from
  mFileReaderController->start();
}

void Controller::configureFileWriterController()
{
  //todo figure out a way to pass configurations...
  //specify the filename ot write to.
  mFileWriterController->start();
}

void Controller::configureDataSenderController()
{
  //todo figure out how to report configuration options...
  //specify the ip and port to connect to.
  mDataSenderController->start();
}

