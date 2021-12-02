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

  Tag(){
    kind = 0;
    type = 0;
    size = 0;
    next = 0;
    data = NULL;
  };

  ~Tag(){
    if(data)
    {
      delete [] (static_cast<char *>(data));
    }
  };

  Tag& operator = (const Tag& rhs)
  {
    kind = rhs.kind;
    type = rhs.type;
    size = rhs.size;
    next = rhs.next;

    void* temp_data = new char[size];

    if(rhs.data && size > 0)
    {
      memcpy(temp_data, rhs.data, static_cast<size_t>(size));
    }
    else
    {
      temp_data = NULL;
    }

    if(data)
    {
      delete [] (static_cast<char *>(data));
    }
    data = temp_data;

    return *this;
  };

  friend std::ostream& operator<<(std::ostream& output, const Tag& tag)
  {
    output << "Tag:\n";
    output << "Kind - " << tag.kind << "\n";
    output << "Type - " << tag.type << "\n";
    output << "Size - " << tag.size << "\n";
    output << "Next - " << tag.next << "\n";
    output << "Data - " << tag.data << "\n";
    return output;
  }
};

}//namespace
#endif // NEUROMAG2MNE_FIFF_HPP
