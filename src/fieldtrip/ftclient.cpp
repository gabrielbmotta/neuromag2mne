#include "ftclient.hpp"
#include <cstring>
#include <iostream>

#include "ftmessage.hpp"

fieldtrip::FtClient::FtClient()
{
}

/*
Attempts to connect to a fieldtrip buffer at the given address and port.
*/
void fieldtrip::FtClient::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

void fieldtrip::FtClient::disconnect()
{

}

/*
Returns whether client is conected to a fieldtrip buffer.
*/
bool fieldtrip::FtClient::isConnected() const
{
  return mSocket.isConnected();
}

/*
Gets response from buffer.
 */
fieldtrip::messagedef_t fieldtrip::FtClient::getResponse()
{
  std::string bufferResponseString = mSocket.receive_blocking();

  messagedef_t resp;
  memcpy(&resp, bufferResponseString.c_str(), sizeof(messagedef_t));

  return resp;
}

void fieldtrip::FtClient::sendHeader(const fieldtrip::FtHeader &header)
{
  if(!mSocket.isConnected()){
    return;
  }

  sendMessage(fieldtrip::FtMessage::headerMessage(header));

  messagedef_t response = getResponse();
  (void)response;
}

void fieldtrip::FtClient::sendData(const FtData &data)
{
  //todo: implement
  (void)data;
}

void fieldtrip::FtClient::sendMessage(const fieldtrip::FtMessage &message)
{
  if(!mSocket.isConnected()){
    return;
  }
  mSocket.send(message.data(), message.size());
}
