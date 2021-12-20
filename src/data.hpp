#ifndef NEUROMAG2MNE_DATA_HPP
#define NEUROMAG2MNE_DATA_HPP

#include "fiff/fifftag.hpp"
#include "utils/sharedpointer.hpp"

struct Data{
  //very temporary todo: change asap
  SharedPointer<fiff::Tag> tag;
  float value;
};

#endif //NEUROMAG2MNE_DATA_HPP
