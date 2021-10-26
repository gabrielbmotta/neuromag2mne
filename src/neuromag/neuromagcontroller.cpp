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

void neuromag::addDataToQueue(SharedPointer<Data> data, void* ptr)
{
  NeuromagController* NMController = static_cast<NeuromagController*>(ptr);
  NMController->mDataQueue->push(data);
}

neuromag::NeuromagController::NeuromagController()
: mContinueRunning(false),
  mAcquisitionSoftwareRunning(false),
  muSecondsSleepTime(100)
{

}

neuromag::NeuromagController::~NeuromagController()
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
//  mCommandWatcher->registerCallback(
//      StringCallbackPair<NeuromagController>("wkup", &NeuromagController::signalAcquisitionSoftwareRunning, this) );
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
  mDataWatcher->registerCallback(addDataToQueue, this);
}

void neuromag::NeuromagController::stop()
{
  mContinueRunning = false;
}
