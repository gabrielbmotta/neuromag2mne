#ifndef NEUROMAG2MNE_FTHEADER_HPP
#define NEUROMAG2MNE_FTHEADER_HPP

#include "fieldtriptypes.hpp"
#include "../utils/bytearray.hpp"
#include <list>

namespace fieldtrip {

class FtHeaderChunk;

class FtHeader {
public:
  size_t size() const;
  void *data() const;

private:
  ByteArray mByteArray;
};

class FtHeaderChunk {
  size_t size() const;
  void *data() const;

private:
  ByteArray mByteArray;
};

class FtHeaderFormater {
  friend class FtHeader;

public:
  static FtHeader simpleHeader(const BufferParameters &parameters);

  static FtHeader neuromagHeader(const BufferParameters &parameters,
                                 FtHeaderChunk neuromagHeaderChunk,
                                 FtHeaderChunk isotrakHeaderChunk);

  static FtHeader extededHeader(const BufferParameters &parameters,
                                const std::list<FtHeaderChunk*>& chunks);
  //todo: add generic header build function that just takes a list of header chunks


private:
  static void appendHeaderChunk(const FtHeader &header,
                                const FtHeaderChunk &chunk);


  static headerdef_t headerdefFromParam(const fieldtrip::BufferParameters &parameters);

private:
  FtHeaderFormater();
};

} // namespace fieldtrip

#endif //NEUROMAG2MNE_FTHEADER_HPP
