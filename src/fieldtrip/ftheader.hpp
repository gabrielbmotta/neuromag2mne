#ifndef NEUROMAG2MNE_FTHEADER_HPP
#define NEUROMAG2MNE_FTHEADER_HPP

#include "fieldtriptypes.hpp"
#include "utils/bytearray.hpp"
#include <list>
#include <cstring>

namespace fieldtrip {

class FtHeaderChunk;

class FtHeader {
public:
  size_t size() const;
  void *data() const;

  static FtHeader simpleHeader(const BufferParameters &parameters);
  static FtHeader extededHeader(const BufferParameters &parameters,
                                const std::list<FtHeaderChunk*>& chunks);
private:
  void appendHeaderChunk(const FtHeaderChunk &chunk);
  void setHeaderdef(const headerdef_t &headerdef);
  ByteArray mByteArray;
};

class FtHeaderChunk {
  size_t size() const;
  void *data() const;

  FtHeaderChunk fromFile(const std::string &filename);
private:
  ByteArray mByteArray;
};

} // namespace fieldtrip

#endif //NEUROMAG2MNE_FTHEADER_HPP
