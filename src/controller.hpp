//CONTROLLER
#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <queue>

#include "neuromag2mne.hpp"
#include "utils/scopedpointer.hpp"
#include "utils/sharedpointer.hpp"

class InputArgumentsParser;
namespace Neuromag { class NeuromagController; }
namespace RandomData { class RandomDataController;}
namespace Fiff { class FileController; }
namespace DataSender { class DataSenderController; }

//todo super temp do not ship
//todo this probably needs to be something of more entity... :)
struct Data{
  int temp;
};

class Controller
{
public:
  Controller();
  void start();
  void stop();
  void parseInputArguments(int argc, char* argv[]);

private:
  enum SourceModeType
  {
    NEUROMAG,
    RANDOM_DATA,
    FILE_READ
  };
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
  int muSecondsSleepTime;

  bool mVerboseMode;
  SourceModeType mSourceMode;
  std::string mFileNameToRead;
  bool mSendDataMode;
  bool mSaveToFileMode;
  std::string mFileNameToSave;

  ScopedPointer<InputArgumentsParser> mInputArgumentsController;

  ScopedPointer<Neuromag::NeuromagController> mNeuromagController;
  ScopedPointer<RandomData::RandomDataController> mRandomDataController;
  ScopedPointer<Fiff::FileController> mFileReaderController;

  ScopedPointer<DataSender::DataSenderController> mDataSenderController;
  ScopedPointer<Fiff::FileController> mFileWriterController;

  ScopedPointer<std::queue<SharedPointer<Data> > > mDataQueue;
};

#endif // CONTROLLER

