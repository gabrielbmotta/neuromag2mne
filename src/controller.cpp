
#include <unistd.h> // for sleep.
#include <cstdlib>
#include "controller.hpp"
#include "inputargumentsparser.hpp"
#include "neuromag/neuromagcontroller.hpp"
#include "randomData/randomdatacontroller.hpp"
#include "fiff/filecontroller.hpp"
#include "dataSender/datasendercontroller.hpp"


Controller::Controller()
    : mContinueRunning(false),
      muSecondsSleepTime(100),
      mVerboseMode(false), // todo still we need to add a verbose thing a log system.
      mSourceMode(NEUROMAG),
      mSendDataMode(true),
      mSaveToFileMode(false)
//      mDataQueue(new DataQueue()) todo MAKE SURE we review this
{

}

Controller::~Controller()
{

}

void Controller::parseInputArguments(const int argc, char* argv[])
{
  OptionsPack parsingResult = mInputArgumentsController->parse(argc, argv);
  checkErrorWhileParsing();
  checkIfDisplayHelp(parsingResult);
  configureSources(parsingResult);
  configureSinks(parsingResult);
}

void Controller::configureSinks(const OptionsPack &parsingResult)
{
  if ( parsingResult.dontSendDataMode )
  {
    mSendDataMode = false;
  }
  if ( parsingResult.saveToFileMode )
  {
    mSaveToFileMode = true;
    mFileNameToSave = parsingResult.fileNameToSave;
  }
}

void Controller::configureSources(const OptionsPack &parsingResult)
{
  mVerboseMode = parsingResult.verboseMode;
  if ( parsingResult.randomDataMode )
  {
    mSourceMode = RANDOM_DATA;
  } else if ( parsingResult.readFromFileMode )
  {
    mSourceMode = FILE_READ;
    mFileNameToRead = parsingResult.fileNameToRead;
  }
}

void Controller::checkIfDisplayHelp(const OptionsPack &parsingResult)
{
  if ( parsingResult.displayHelp )
  {
    displayHelp(mInputArgumentsController->getHelpStr());
    exit(0);
  }
}

void Controller::checkErrorWhileParsing()
{
  if ( mInputArgumentsController->errorWhileParsingOptions() )
  {
    std::cout << "Something went wrong parsing commandline input options.\n";
    displayHelp(mInputArgumentsController->getHelpStr());
    exit(1);
  }
}

void Controller::start()
{
  std::cout << "=== Controller Startup ===\n";
  if( mSourceMode == NEUROMAG ) {
    configureNeuromagController();
  } else if( mSourceMode == RANDOM_DATA ) {
    configureRandomDataController();
  } else if( mSourceMode == FILE_READ ) {
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
    usleep(muSecondsSleepTime);
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
    if ( mSendDataMode )
    {
//      mDataSenderController->send(mDataQueue.front());
    }
    if ( mSaveToFileMode )
    {
//      mFileWriterController->write(mDataQueue.front());
    }
    mDataQueue->pop();
  }
}

bool Controller::dataAvailable() const
{
  return !mDataQueue->empty();
}

void Controller::stop()
{
  mContinueRunning = false;
}

void Controller::displayHelp(const std::string& helpString)
{
  //todo preamble name date etc...
  std::cout << "\n";
  std::cout << "Neuromag2MNE\n";
  std::cout << "Version. " << versionMayor << "." << versionMinor << "\n";
  std::cout << helpString;
  std::cout << "\n";
}

void Controller::prepareToExitApplication()
{
  if( mSourceMode == NEUROMAG ) {
    mNeuromagController->stop();
  } else if( mSourceMode == RANDOM_DATA ) {
    mRandomDataController->stop();
  } else if( mSourceMode == FILE_READ ) {
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
  mNeuromagController->setSharedQueue(mDataQueue);
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

