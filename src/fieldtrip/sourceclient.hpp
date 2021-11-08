#ifndef NEUROMAG2MNE_SOURCECLIENT_HPP
#define NEUROMAG2MNE_SOURCECLIENT_HPP

#include <string>
#include <list>

namespace fieldtrip {

struct HeaderChunk{
  int temp;
};

struct BufferParameters{
  int temp;
};

class SourceClient {

  SourceClient();

  void connect(std::string address, int port);
  void sendHeader(BufferParameters param);
  void sendHeader(BufferParameters param, std::list<HeaderChunk> chunkList);

};

}//namespace

#endif //NEUROMAG2MNE_SOURCECLIENT_HPP
