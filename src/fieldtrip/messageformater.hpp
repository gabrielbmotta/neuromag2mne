#ifndef NEUROMAG2MNE_MESSAGEFORMATER_HPP
#define NEUROMAG2MNE_MESSAGEFORMATER_HPP

#include "fieldtriptypes.hpp"
#include <string>
#include <cstring>
#include <utility>

namespace fieldtrip{

//todo: do this with smart pointers
//      so we don't have to manually
//      tag these as 'done'.

/*
Container for a byte array to be sent to an instance of fieldtrip buffer.
*/
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
  static Message simpleHeader(const fieldtrip::BufferParameters& parameters);

  static Message neuromagHeader(const fieldtrip::BufferParameters& parameters,
                                const std::string& neuromagHeaderPath,
                                const std::string& isotrakHeaderPath);

  static Message rawDataMessage(const fieldtrip::BufferParameters& parameters,
                                char* data,
                                size_t dataSize);

private:
  static messagedef_t putHeaderMessagedef();
  static messagedef_t putDataMessagedef();
  static headerdef_t headerdefFromParam(const fieldtrip::BufferParameters& parameters);
  static datadef_t datadefFromParam(fieldtrip::BufferParameters parameters);
  static std::pair<char*, size_t> getByteArrayFromFile(const std::string& path);
  static void appendHeaderChunk(char* messageByteArray,
                                std::pair<char*, size_t>& chunk,
                                int chunkID,
                                size_t & offset);

  MessageFormater();
};

}//namespace
#endif //NEUROMAG2MNE_MESSAGEFORMATER_HPP
