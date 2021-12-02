//
// Created by Gabriel Motta on 12/1/21.
//

#ifndef NEUROMAG2MNE_FTHEADER_HPP
#define NEUROMAG2MNE_FTHEADER_HPP

namespace fieldtrip {

class FtHeader {
public:
  FtHeader(): mHeaderByteArray(NULL), mSize(0){};
  FtHeader(const FtHeader& header);
  ~FtHeader();

  static FtHeader simpleHeader(const BufferParameters& parameters);

  static FtHeader neuromagHeader(const BufferParameters& parameters,
                                 std::string neuromagHeaderChunkFile,
                                 std::string isotrakHeaderChunkFile);

  FtHeader& operator=(const FtHeader& other);

  size_t size() const;
  void* data() const;
private:
  char* mHeaderByteArray;
  size_t mSize;

  static headerdef_t headerdefFromParam(const fieldtrip::BufferParameters& parameters);

  static void appendHeaderChunk(char* headerByteArray,
                                std::pair<char*, size_t>& chunk,
                                int chunkID,
                                size_t & offset);
};

}

#endif //NEUROMAG2MNE_FTHEADER_HPP
