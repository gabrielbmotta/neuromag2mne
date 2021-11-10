#ifndef NEUROMAG2MNE_FTCLIENT_HPP
#define NEUROMAG2MNE_FTCLIENT_HPP

#include <string>
#include <vector>

#include "../utils/tcpsocket.hpp"
#include "../data.hpp"
#include "../utils/sharedpointer.hpp"
#include "fieldtriptypes.hpp"

namespace fieldtrip {

struct HeaderChunk{
  std::string filePath;
};

struct BufferParameters{
  int nChannels;
  float sampleFrequency;
  int dataType;
};

class Client {
public:
  Client();

  void connect(std::string address, unsigned short port);
  void sendHeader(const BufferParameters& param);
  void sendHeader(const BufferParameters& param, std::vector<HeaderChunk> chunkList);

  void sendData(SharedPointer<Data> data);

  bool isConnected() const;

private:
  void sendHeaderChunk(HeaderChunk chunk);

  void formatHeader(header_t* header, const BufferParameters& param) const;

  TCPSocket mSocket;
};

}//namespace

#endif //NEUROMAG2MNE_FTCLIENT_HPP
