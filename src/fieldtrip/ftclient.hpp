#ifndef NEUROMAG2MNE_FTCLIENT_HPP
#define NEUROMAG2MNE_FTCLIENT_HPP

#include <string>
#include <vector>

#include "../utils/tcpsocket.hpp"
#include "../data.hpp"
#include "../utils/sharedpointer.hpp"

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
  void sendHeader(BufferParameters param);
  void sendHeader(BufferParameters param, std::vector<HeaderChunk> chunkList);

  void sendData(SharedPointer<Data> data);

  bool isConnected() const;

private:
  void sendHeaderChunk(HeaderChunk chunk);

  TCPSocket mSocket;
};

}//namespace

#endif //NEUROMAG2MNE_FTCLIENT_HPP
