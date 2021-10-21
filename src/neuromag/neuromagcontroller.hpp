#ifndef NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
#define NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP

#include "../utils/scopedpointer.hpp"
#include "commandwatcher.hpp"
#include "datawatcher.hpp"

class NeuromagController
{
  friend void acquisitionSoftwareRunning(void* ptr);
public:
  NeuromagController();
  void start();
private:

  void configureCommandWatcher();
  void configureCommandWatcherCallbacks();
  void configureDataWatcher();
  void configureDataWatcherCallbacks();

  bool mContinueRunning;
  bool mAcquisitionSoftwareRunning;
  ScopedPointer<Neuromag::CommandWatcher> mCommandWatcher;
  ScopedPointer<Neuromag::DataWatcher> mDataWatcher;
};


#endif //NEUROMAG2MNE_NEUROMAGCONTROLLER_HPP
