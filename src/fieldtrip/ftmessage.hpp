#ifndef NEUROMAG2MNE_FTMESSAGE_HPP
#define NEUROMAG2MNE_FTMESSAGE_HPP

#include "fieldtriptypes.hpp"
#include "ftheader.hpp"
#include "ftdata.hpp"
#include "utils/bytearray.hpp"
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
class FtMessage {
  friend class FtMessageFormater;
public:
  FtMessage();

  size_t size() const;
  void* data() const;

  static FtMessage headerMessage(const FtHeader& header);
  static FtMessage dataMessage(const FtData& data);

private:
  void setMessageDef(const messagedef_t& messagedef);
  void setMessageContent(const void* data, size_t size);

  ByteArray mByteArray;
};

}//namespace
#endif //NEUROMAG2MNE_FTMESSAGE_HPP
