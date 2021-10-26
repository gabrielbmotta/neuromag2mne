#ifndef NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
#define NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP

#include "../utils/scopedpointer.hpp"
#include "../utils/multithreadqueue.hpp"
#include "../utils/data.hpp"
#include "../utils/sharedpointer.hpp"

namespace neuromag{

void addDataToQueue(SharedPointer<Data>, void*);

class CommandWatcher;
class DataWatcher;

class NeuromagController
{
  //  friend void acquisitionSoftwareRunning(void* ptr);
  friend void addDataToQueue(SharedPointer<Data>, void*);

public:
  NeuromagController();
  ~NeuromagController();
  void start();
  void stop();

  void setSharedQueue(SharedPointer<MultiThreadQueue<SharedPointer<Data> > >);

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

  SharedPointer<MultiThreadQueue<SharedPointer<Data> > > mDataQueue;
};

}

#endif //NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
