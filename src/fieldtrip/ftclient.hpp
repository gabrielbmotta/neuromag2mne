#ifndef NEUROMAG2MNE_FTCLIENT_HPP
#define NEUROMAG2MNE_FTCLIENT_HPP

#include <string>
#include <vector>

#include "../utils/tcpsocket.hpp"
#include "../data.hpp"
#include "../utils/sharedpointer.hpp"

#include "fieldtriptypes.hpp"
#include "ftheader.hpp"
#include "ftmessage.hpp"

namespace fieldtrip {

class FtClient {
public:
  FtClient();

  void connect(std::string address, unsigned short port);
  void disconnect();
  bool isConnected() const;

  void sendHeader(const FtHeader& header);
  void sendData(const Data& data);

private:
  void sendMessage(const FtMessage& message);
  messagedef_t getResponse();

  TCPSocket mSocket;
};

}//namespace

#endif //NEUROMAG2MNE_FTCLIENT_HPP
