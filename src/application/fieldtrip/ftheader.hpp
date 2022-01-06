#ifndef NEUROMAG2MNE_FTHEADER_HPP
#define NEUROMAG2MNE_FTHEADER_HPP

#include "fieldtriptypes.hpp"
#include "application/utils/bytearray.hpp"
#include <list>
#include <cstring>

namespace fieldtrip {

class FtHeaderChunk;

class FtHeader {
public:
  size_t size() const;
  void *data() const;

  static FtHeader simpleHeader(const BufferParameters &parameters);
  static FtHeader extendedHeader(const BufferParameters &parameters,
                                 const std::list<FtHeaderChunk*>& chunks);
private:
  void appendHeaderChunk(const FtHeaderChunk &chunk);
  void setHeaderdef(const headerdef_t &headerdef);
  ByteArray mByteArray;
};

class FtHeaderChunk {
public:
  size_t size() const;
  void *data() const;

  static FtHeaderChunk fromFile(const std::string &filename, int chunkId);
  static size_t totalSize(const std::list<FtHeaderChunk*>&);
private:
  void setChunkDef(const chunkdef_t &chunkdef);
  void setChunkContents(const void* data, size_t size);

  ByteArray mByteArray;
};

} // namespace fieldtrip

#endif //NEUROMAG2MNE_FTHEADER_HPP
