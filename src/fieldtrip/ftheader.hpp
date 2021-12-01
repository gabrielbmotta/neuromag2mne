//
// Created by Gabriel Motta on 12/1/21.
//

#ifndef NEUROMAG2MNE_FTHEADER_HPP
#define NEUROMAG2MNE_FTHEADER_HPP

namespace fieldtrip {

class Header {
public:
  static Header simpleHeader(const BufferParameters& parameters);
  static Header neuromagHeader(const BufferParameters& parameters,
                               std::string neuromagHeaderChunkFile,
                               std::string isotrakHeaderChunkFile);



private:
  void* mHeaderdata;
  int mSize;

  static headerdef_t headerdefFromParam(const fieldtrip::BufferParameters& parameters);


  static void appendHeaderChunk(char* headerByteArray,
                                std::pair<char*, size_t>& chunk,
                                int chunkID,
                                size_t & offset);

  Header(){};

};

}

#endif //NEUROMAG2MNE_FTHEADER_HPP
