#ifndef NEUROMAG2MNE_MESSAGEFORMATER_HPP
#define NEUROMAG2MNE_MESSAGEFORMATER_HPP

#include "fieldtriptypes.hpp"
#include <string>
#include <cstring>

namespace fieldtrip{

//todo: do this with smart pointers
//      so we don't have to manually
//      tag these as 'done'.

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
                                const std::string& neuromagHeaderPath,
                                const std::string& isotrakHeaderPath);

private:
  static messagedef_t* putHeaderMessage();
  static headerdef_t* defaultHeader();

  MessageFormater();
};

}//namespace
#endif //NEUROMAG2MNE_MESSAGEFORMATER_HPP
