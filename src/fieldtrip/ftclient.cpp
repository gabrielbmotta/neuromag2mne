#include "ftclient.hpp"
#include <cstring>
#include <iostream>

#include "messageformater.hpp"

fieldtrip::Client::Client()
{
}

/*
Attempts to connect to a fieldtrip buffer at the given address and port.
*/
void fieldtrip::Client::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

/*
Attempts to send a header to the connected buffer based on the given buffer parameters.
*/
void fieldtrip::Client::sendHeader(const BufferParameters& parameters)
{
  if(!mSocket.isConnected()){
    return;
  }

  fieldtrip::Message headerMessage = fieldtrip::MessageFormater::simpleHeader(parameters);
  mSocket.send(headerMessage.content, headerMessage.size);

  messagedef_t response = getResponse();
  (void)response;
}

/*
Attempts to send a header to the connected buffer based on the given buffer parameters and files.
*/
void fieldtrip::Client::sendNeuromagHeader(const BufferParameters& parameters,
                                           std::string neuromagHeaderChunkFile,
                                           std::string isotrakHeaderChunkFile)
{
  fieldtrip::Message headerMessage = fieldtrip::MessageFormater::neuromagHeader(parameters, 
                                                                                neuromagHeaderChunkFile, 
                                                                                isotrakHeaderChunkFile);

  mSocket.send(headerMessage.content, headerMessage.size);
  
  messagedef_t response = getResponse();
  (void)response;
}

void fieldtrip::Client::sendData(SharedPointer<Data> data)
{
  //to do: implement
  (void)data;
}

/*
Returns whether client is conected to a fieldtrip buffer.
*/
bool fieldtrip::Client::isConnected() const
{
  return mSocket.isConnected();
}

/*
Gets response from buffer.
 */
messagedef_t fieldtrip::Client::getResponse()
{
  std::string bufferResponseString = mSocket.receive_blocking();

  messagedef_t resp;
  memcpy(&resp, bufferResponseString.c_str(), sizeof(messagedef_t));

  return resp;
}
