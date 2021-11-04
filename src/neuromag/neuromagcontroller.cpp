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
void neuromag::aquisitionSoftwareStartingCallback(void* data,void* ptr)
{
  (void)data;

  neuromag::NeuromagController* NMC = static_cast<neuromag::NeuromagController*>(ptr);
  NMC->configureDataWatcher();
}


neuromag::NeuromagController::NeuromagController()
: mContinueRunning(false),
  mAcquisitionSoftwareRunning(false),
  muSecondsSleepTime(100)
{
  muSecondsSleepTime = 100;
}

neuromag::NeuromagController::~NeuromagController()
{

}

void neuromag::NeuromagController::start()
{
  configureCommandWatcher();
  //configureDataWatcher();
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
  mCommandWatcher->registerCallback("wkup", aquisitionSoftwareStartingCallback, this);
//  mCommandWatcher->registerCallback(
//      StringCallbackPair<NeuromagController>("wkup", &NeuromagController::signalAcquisitionSoftwareRunning, this) );

  mCommandWatcher->showCallbacks();
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
  mDataWatcher->showCallbacks();
}

void neuromag::NeuromagController::stop()
{
  mContinueRunning = false;
}

void neuromag::NeuromagController::registerDataCallback(void (*function)(SharedPointer<Data>, void*), void* ptr)
{
  mDataWatcher->registerCallback(function, ptr);
}
