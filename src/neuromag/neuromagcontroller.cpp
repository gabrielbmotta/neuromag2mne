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

Neuromag::NeuromagController::NeuromagController()
: mContinueRunning(false),
  mAcquisitionSoftwareRunning(false),
  muSecondsSleepTime(100)
{

}

void Neuromag::NeuromagController::start()
{
  configureCommandWatcher();
}

void Neuromag::NeuromagController::configureCommandWatcher()
{
  configureCommandWatcherCallbacks();
  mCommandWatcher->connect();
  mCommandWatcher->startWatching();
}

void Neuromag::NeuromagController::configureCommandWatcherCallbacks()
{
  std::cout << "Registering CommandWatcher callbacks.\n";
  mCommandWatcher->registerCallback(
      StringCallbackPair<NeuromagController>("wkup", &NeuromagController::signalAcquisitionSoftwareRunning, this) );
}

void Neuromag::NeuromagController::signalAcquisitionSoftwareRunning()
{
  mAcquisitionSoftwareRunning = true;
}

void Neuromag::NeuromagController::configureDataWatcher()
{
  configureDataWatcherCallbacks();
  mDataWatcher->connect();
  mDataWatcher->startWatching();
}

void Neuromag::NeuromagController::configureDataWatcherCallbacks()
{
//  std::cout << "Registering DataWatcher callbacks.\n";
//  mDataWatcher->registerCallback("xxx", testCallback1, this);
}

void Neuromag::NeuromagController::stop()
{
  mContinueRunning = false;
}