#include "neuromagcontroller.hpp"

#include <unistd.h> // for sleep.
#include <iostream>

#include "../utils/stringcallbackpair.hpp"
#include "commandwatcher.hpp"
#include "datawatcher.hpp"

////free function
//void acquisitionSoftwareRunning(void* mPtr)
//{
//  std::cout << "Acquisition software has been started.\n";
//  NeuromagController* c(static_cast<NeuromagController*>(mPtr));
//  c->mAcquisitionSoftwareRunning = true;
//}

neuromag::NeuromagController::NeuromagController()
: mContinueRunning(false),
  mAcquisitionSoftwareRunning(false),
  muSecondsSleepTime(100)
{

}

void neuromag::NeuromagController::start()
{
  configureCommandWatcher();
}

void neuromag::NeuromagController::configureCommandWatcher()
{
  configureCommandWatcherCallbacks();
  mCommandWatcher->connect();
  mCommandWatcher->startWatching();
}

void neuromag::NeuromagController::configureCommandWatcherCallbacks()
{
  std::cout << "Registering CommandWatcher callbacks.\n";
  mCommandWatcher->registerCallback(
      StringCallbackPair<NeuromagController>("wkup", &NeuromagController::signalAcquisitionSoftwareRunning, this) );
}

void neuromag::NeuromagController::signalAcquisitionSoftwareRunning()
{
  mAcquisitionSoftwareRunning = true;
}

void neuromag::NeuromagController::configureDataWatcher()
{
  configureDataWatcherCallbacks();
  mDataWatcher->connect();
  mDataWatcher->startWatching();
}

void neuromag::NeuromagController::configureDataWatcherCallbacks()
{
//  std::cout << "Registering DataWatcher callbacks.\n";
//  mDataWatcher->registerCallback("xxx", testCallback1, this);
}

void neuromag::NeuromagController::stop()
{
  mContinueRunning = false;
}