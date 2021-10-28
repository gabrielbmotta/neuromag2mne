#ifndef NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
#define NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP

#include "../utils/scopedpointer.hpp"
#include "../utils/multithreadqueue.hpp"
#include "../utils/data.hpp"
#include "../utils/sharedpointer.hpp"

namespace neuromag{


class CommandWatcher;
class DataWatcher;

class NeuromagController
{
public:
  NeuromagController();
  ~NeuromagController();
  void start();
  void stop();

  void registerDataCallback(void (*function)(SharedPointer<Data>, void* pointer), void*);

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
