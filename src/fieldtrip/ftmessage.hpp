#ifndef NEUROMAG2MNE_FTMESSAGE_HPP
#define NEUROMAG2MNE_FTMESSAGE_HPP

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
struct FtMessage {
  FtMessage();
  FtMessage(char* message_ptr,
            size_t message_size);
  FtMessage(const FtMessage& other);
  ~FtMessage();

  FtMessage& operator=(const FtMessage& other);

  char*   mMessageByteArray;
  size_t  mSize;
};

class MessageFormater {
public:
  static FtMessage headerMessage(const FtHeader& header);
  static FtMessage dataMessage(const Data& data);

  static FtMessage rawDataMessage(const fieldtrip::BufferParameters& parameters,
                                  char* data,
                                  size_t dataSize);

private:
  static messagedef_t putHeaderMessagedef();
  static messagedef_t putDataMessagedef();
  static datadef_t datadefFromParam(fieldtrip::BufferParameters parameters);
  static std::pair<char*, size_t> getByteArrayFromFile(const std::string& path);
  static void appendHeaderChunk(char* messageByteArray,
                                std::pair<char*, size_t>& chunk,
                                int chunkID,
                                size_t & offset);

  MessageFormater();
};

}//namespace
#endif //NEUROMAG2MNE_FTMESSAGE_HPP
