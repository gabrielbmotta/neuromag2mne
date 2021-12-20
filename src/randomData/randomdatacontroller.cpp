#include <iostream>

#include "randomdatacontroller.hpp"

void* randomData::generateData(void *input)
{
  randomData::RandomDataController* pController = reinterpret_cast<RandomDataController*>(input);
  while(pController->mContinueGenerating)
  {
    SharedPointer<Data> data = pController->createData();
    pController->mCallback(data);
  }

  return NULL;
}

randomData::RandomDataController::RandomDataController()
: mParameters()
, mCallback()
, mThread()
, mContinueGenerating(false)
{
  std::cout << "Creating random data controller.\n";
}

void randomData::RandomDataController::start()
{
  mContinueGenerating = true;
  mThread.startThread(generateData, this);
}

void randomData::RandomDataController::stop()
{

}

void randomData::RandomDataController::setParameters(const randomData::RandomDataController::Parameters& parameters)
{
  mParameters = parameters;
}

void randomData::RandomDataController::setCallback(const randomData::RandomDataController::Callback& callback)
{
  mCallback = callback;
}

void randomData::RandomDataController::setCallback(void (*function)(SharedPointer<Data>, void *), void *pointer)
{
  mCallback = Callback(function, pointer);
}

SharedPointer<Data> randomData::RandomDataController::createData()
{
  SharedPointer<Data> data;

  //create data

  return data;
}
