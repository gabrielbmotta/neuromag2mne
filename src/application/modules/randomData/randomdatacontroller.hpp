#ifndef NEUROMAG2MNE_RANDOMDATACONTROLLER_HPP
#define NEUROMAG2MNE_RANDOMDATACONTROLLER_HPP

#include "application/data.hpp"
#include <stdint.h>
#include <vector>
#include "utils/thread.hpp"

namespace randomData {

void* generateData(void*);


class RandomDataController {
public:
  friend void* generateData(void*);

  struct Parameters{
    Parameters() : sampleFrequency(1000), chunkSize(500), numberOfChannels(20){};
    float sampleFrequency;
    int chunkSize;
    int numberOfChannels;
  };

  struct Callback {
    Callback() : mFunction(NULL), mPointer(NULL) {}
    Callback(void (*function)(SharedPointer<Data>, void* pointer), void* pointer)
            : mFunction(function), mPointer(pointer){};
    void operator()(SharedPointer<Data> in){mFunction(in, mPointer);};
    void (*mFunction)(SharedPointer<Data>, void* pointer);
    void* mPointer;
  };

  RandomDataController();

  void setParameters(const Parameters& parameters);
  void setCallback(const Callback& callback);
  void setCallback(void (*function)(SharedPointer<Data>, void* pointer), void* pointer);

  void start();
  void stop();

private:
  SharedPointer<Data> createData();

  Parameters mParameters;
  Callback mCallback;
  Thread mThread;
  bool mContinueGenerating;

};

}

#endif //NEUROMAG2MNE_RANDOMDATACONTROLLER_HPP
