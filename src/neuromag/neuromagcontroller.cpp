#include "neuromagcontroller.hpp"

#include <iostream>

//free function
void acquisitionSoftwareRunning(void* ptr)
{
  std::cout << "Acquisition software has been started.\n";
  NeuromagController* c(static_cast<NeuromagController*>(ptr));
  c->mAcquisitionSoftwareRunning = true;
}

NeuromagController::NeuromagController()
: mContinueRunning(false),
  mAcquisitionSoftwareRunning(false)
{

}

void NeuromagController::start()
{

}

void NeuromagController::configureCommandWatcher()
{
  configureCommandWatcherCallbacks();
  mCommandWatcher->connect();
  mCommandWatcher->startWatching();
}

void NeuromagController::configureCommandWatcherCallbacks()
{
  std::cout << "Registering CommandWatcher callbacks.\n";
  mCommandWatcher->registerCallback("wkup", acquisitionSoftwareRunning, this);
  mCommandWatcher->showCallbacks();
}

void NeuromagController::configureDataWatcher()
{
  configureDataWatcherCallbacks();
  mDataWatcher->connect();
  mDataWatcher->startWatching();
}

void NeuromagController::configureDataWatcherCallbacks()
{
//  std::cout << "Registering DataWatcher callbacks.\n";
//  mDataWatcher->registerCallback("xxx", testCallback1, this);
}