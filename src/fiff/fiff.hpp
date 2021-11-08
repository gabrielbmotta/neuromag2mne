#include <stdint.h>
#include <iostream>

// FIFF.HPP
#ifndef NEUROMAG2MNE_FIFF_HPP
#define NEUROMAG2MNE_FIFF_HPP

//Tags
#define FIFF_NCHAN          200
#define FIFF_SFREQ          201

//Block Tags
#define FIFF_BLOCK_START    104
#define FIFF_BLOCK_END      105

//Block Types
#define FIFFB_RAW_DATA      102

namespace fiff {

struct Tag {
  int32_t kind;   // Tag number.
  int32_t type;   // Data type.
  int32_t size;   // Size of data.
  int32_t next;   // Next object. 0 is sequential, -1 if end of file.
  void*   data;   // Pointer to data.

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
