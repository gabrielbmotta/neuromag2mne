
#include "controller.hpp"
#include <unistd.h>

#include "utils/commandlineoptionsparser.hpp"

void acquisitionSoftwareRunning(void* ptr)
{
    std::cout << "Acquisition software has been started.\n";
    Controller* c(static_cast<Controller*>(ptr));
    c->mAcquisitionSoftwareRunning = true;
}

// =========================================================================

Controller::Controller()
: mIsActive(false),
  mAcquisitionSoftwareRunning(false),
  mContinueRunning(false),
  mOptionsParsed(false),
  mCallbacksConfigured(false),
  uSecondsSleepTime(100)
{

}

void Controller::start()
{
  std::cout << "=== Controller Startup ===\n";
  configureCommandWatcher();
  configureDataWatcher();

  if ( configurationIsReady() )
  {
    mContinueRunning = true;
    run();
  }
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
  mCallbacksConfigured = true;
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

void Controller::printCommand(const std::string& s) const
{
    std::cout << s << "\n";
}

void Controller::parseInputArguments(const int argc, char* argv[])
{
  std::cout << "Parsing options!!\n";
  //     std::vector<std::string> opt1Flags;
//     opt1Flags.push_back("-dsfs");
//     std::vector<std::string> opt1Help;
//     opt1Help.push_back("This is my second help");
//     CommandlineOption opt1("option1", opt1Flags, opt1Help, WITHOUT_VALUE);

//     std::vector<std::string> opt2Flags;
//     opt2Flags.push_back("-f");
//     opt2Flags.push_back("--file");
//     std::vector<std::string> opt2Help;
//     opt2Help.push_back("this is my help");
//     opt2Help.push_back("Because this is my second example.");
//     CommandlineOption opt2("option2", opt2Flags, opt2Help, CommandlineOption::WITH_VALUE);

//     CommandlineOption opt3(opt1);
//     opt3.name = std::string("option3");
//     // opt3.flagsList[0] = std::string("-ff");
//     // opt3.flagsList[1] = std::string("--ffile");
//     // opt3.helpString[0] = "this is my help modified";
//     // opt3.helpString.pop_back();

//     std::vector<std::string> opt4Flags;
//     opt4Flags.push_back("-h");
//     opt4Flags.push_back("--help");
//     std::vector<std::string> opt4Help;
//     opt4Help.push_back("this is the HELP!!");
//     opt4Help.push_back("Because this is my second example.");
//     CommandlineOption opt4("help", opt4Flags, opt4Help, WITHOUT_VALUE);

//     // if( opt2.hasFlag("-f") )
//     // {
//     //     std::cout << "it has the flag!!\n";
//     // } else {
//     //     std::cout << "it doesn't have the flag!!\n";
//     // }

//     CommandlineOptionsParser parser;
//     parser.addOption(opt1);
//     parser.addOption(opt2);
//     parser.addOption(opt3);
//     parser.addOption(opt4);
//     parser.setStopOnError(false);

//     parser.parse(argc, argv);

//     if( parser.allOptionsParsedCorrectly() )
//     {
//         testOption(parser, "option1");
//         testOption(parser, "option2");
//         testOption(parser, "option3");
//         testOption(parser, "help");
//     }


//     std::cout << parser.getHelpDescription();
  mOptionsParsed = true;
}

bool Controller::configurationIsReady() const
{
  bool allGood(true);

  if ( mOptionsParsed )
  {
    std::cout << "Options parsed ok. \n";
  }
  else
  {
    std::cout << "Something went wrong while parsing the options.\n";
    allGood = false;
  }

  //todo continue... with other options...

  return allGood;
}

bool Controller::dataAvailable()
{
  return !mDataQueue.empty();
}