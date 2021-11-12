#ifndef NEUROMAG2MNE_MESSAGEFORMATER_HPP
#define NEUROMAG2MNE_MESSAGEFORMATER_HPP

#include "fieldtriptypes.hpp"
#include <string>

namespace fieldtrip{

//to do:  do this with smart pointers
//        so we don't have to manually
//        tag these as 'done'.

struct Message {
  Message();
  Message(char* message_ptr,
          size_t message_size);

  char*   content;
  size_t  size;

  void done();
};

class MessageFormater {
public:
  static Message simpleHeader(fieldtrip::BufferParameters parameters);

  static Message neuromagHeader(fieldtrip::BufferParameters parameters,
                                std::string neuromagHeaderPath,
                                std::string isotrakHeaderPath);
};

}//namespace
#endif //NEUROMAG2MNE_MESSAGEFORMATER_HPP
