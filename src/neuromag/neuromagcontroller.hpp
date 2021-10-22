#ifndef NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
#define NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP

#include "../utils/scopedpointer.hpp"

namespace neuromag{

class CommandWatcher;
class DataWatcher;

class NeuromagController
{
  friend void acquisitionSoftwareRunning(void* ptr);
public:
  NeuromagController();
  ~NeuromagController();
  void start();
  void stop();

  void signalAcquisitionSoftwareRunning();

private:

  void configureCommandWatcher();
  void configureCommandWatcherCallbacks();
  void configureDataWatcher();
  void configureDataWatcherCallbacks();

  bool mContinueRunning;
  bool mAcquisitionSoftwareRunning;
  int muSecondsSleepTime;
  ScopedPointer<CommandWatcher> mCommandWatcher;
  ScopedPointer<DataWatcher> mDataWatcher;
};

}

#endif //NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
