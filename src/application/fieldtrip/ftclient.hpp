#ifndef NEUROMAG2MNE_FTCLIENT_HPP
#define NEUROMAG2MNE_FTCLIENT_HPP

#include <string>
#include <vector>

#include "application/utils/tcpsocket.hpp"
#include "application/data.hpp"
#include "application/utils/sharedpointer.hpp"

#include "fieldtriptypes.hpp"
#include "ftheader.hpp"
#include "ftdata.hpp"
#include "ftmessage.hpp"

namespace fieldtrip {

class FtClient {
public:
  FtClient();

  void connect(std::string address, unsigned short port);
  void disconnect();
  bool isConnected() const;

  void sendHeader(const FtHeader& header);
  void sendData(const FtData& data);

private:
  void sendMessage(const FtMessage& message);
  messagedef_t getResponse();

  TCPSocket mSocket;
};

}//namespace

#endif //NEUROMAG2MNE_FTCLIENT_HPP
