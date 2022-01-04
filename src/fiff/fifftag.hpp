// FIFF.HPP
#ifndef NEUROMAG2MNE_FIFF_HPP
#define NEUROMAG2MNE_FIFF_HPP
#include <stdint.h>
#include <iostream>
#include <cstring>

#include "fiffdefines.hpp"

namespace fiff {

struct Tag {
  int32_t kind;   // Tag number.
  int32_t type;   // Data type.
  int32_t size;   // Size of data.
  int32_t next;   // Next object. 0 is sequential, -1 if end of file.
  void*   data;   // Pointer to data.
  //todo: decide what to do with data when copying and destructing objects of tag class;
  //      shared pointer?

  Tag();
  Tag(const Tag&);
  ~Tag();

  Tag& operator = (const Tag& rhs);

//  friend std::ostream& operator<<(std::ostream& output, const Tag& tag)
//  {
//    output << "Tag:\n";
//    output << "Kind - " << tag.kind << "\n";
//    output << "Type - " << tag.type << "\n";
//    output << "Size - " << tag.size << "\n";
//    output << "Next - " << tag.next << "\n";
//    output << "Data - " << tag.data << "\n";
//    return output;
//  }
};


Tag samplingFrequencyTag(float samplingFrequency);
Tag numberOfChannelsTag(int32_t numberOfChannels);


}//namespace
#endif // NEUROMAG2MNE_FIFF_HPP
