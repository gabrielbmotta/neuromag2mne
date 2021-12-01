#ifndef NEUROMAG2MNE_FTCLIENT_HPP
#define NEUROMAG2MNE_FTCLIENT_HPP

#include <string>
#include <vector>

#include "../utils/tcpsocket.hpp"
#include "../data.hpp"
#include "../utils/sharedpointer.hpp"
#include "fieldtriptypes.hpp"
#include "ftheader.hpp"

namespace fieldtrip {

class Client {
public:
  Client();

  void connect(std::string address, unsigned short port);

  void sendHeader(const BufferParameters& parameters);
  void sendNeuromagHeader(const BufferParameters& parameters,
                          std::string neuromagHeaderChunkFile,
                          std::string isotrakHeaderChunkFile);

  void sendData(SharedPointer<Data> data);

  void sendHeader(const Header& header);
  void sendData(const Data& data);

  bool isConnected() const;

private:
  messagedef_t getResponse();

  TCPSocket mSocket;
};

}//namespace

#endif //NEUROMAG2MNE_FTCLIENT_HPP
