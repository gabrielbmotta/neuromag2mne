#include <iostream>
#include <unistd.h>

#include "randomdatacontroller.hpp"

void* randomData::generateData(void *input)
{
  randomData::RandomDataController* pController = reinterpret_cast<RandomDataController*>(input);

  SharedPointer<Data> sampleFreq(new Data);
  {
    SharedPointer<fiff::Tag> tag(new fiff::Tag);
    *tag = fiff::samplingFrequencyTag(1000);
    sampleFreq->tag = tag;
  }
  pController->mCallback(sampleFreq);

  SharedPointer<Data> numChannels(new Data);
  {
    SharedPointer<fiff::Tag> tag(new fiff::Tag);
    *tag = fiff::numberOfChannelsTag(pController->mParameters.numberOfChannels);
    numChannels->tag = tag;
  }
  pController->mCallback(numChannels);

  uint uSecSleepTime = static_cast<uint>((static_cast<float>(pController->mParameters.chunkSize)/pController->mParameters.sampleFrequency) * 1000000);

  while(pController->mContinueGenerating)
  {
    SharedPointer<Data> data = pController->createData();
    pController->mCallback(data);
    usleep(uSecSleepTime);
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
  mContinueGenerating = false;
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
  SharedPointer<Data> data(new Data);

  //create data
  {
    SharedPointer<fiff::Tag> tag(new fiff::Tag);
    tag->kind = FIFF_DATA_BUFFER;
    tag->type = FIFFT_INT;

    tag->size = mParameters.numberOfChannels * mParameters.chunkSize * static_cast<int>(sizeof(int32_t));
    size_t intBufferSize = static_cast<size_t>(tag->size) / sizeof(int32_t);

    int* dataBuffer = new int32_t[intBufferSize];
    for (size_t i = 0; i < intBufferSize; ++i)
    {
      dataBuffer[i] = 1;
    }

    tag->data = dataBuffer;

    data->tag = tag;
  }

  return data;
}
