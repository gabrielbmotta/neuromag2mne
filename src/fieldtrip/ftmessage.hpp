#ifndef NEUROMAG2MNE_FTMESSAGE_HPP
#define NEUROMAG2MNE_FTMESSAGE_HPP

#include "fieldtriptypes.hpp"
#include "ftheader.hpp"
#include "ftdata.hpp"
#include "../utils/bytearray.hpp"
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

private:
  ByteArray mByteArray;
};

class FtMessageFormater {
public:
  static FtMessage headerMessage(const FtHeader& header);
  static FtMessage dataMessage(const FtData& data);

private:
  static messagedef_t putHeaderMessagedef();
  static messagedef_t putDataMessagedef();
  static datadef_t datadefFromParam(BufferParameters parameters);

  FtMessageFormater();
};

}//namespace
#endif //NEUROMAG2MNE_FTMESSAGE_HPP
