#include "ftclient.hpp"
#include <cstring>
#include <iostream>

#include "messageformater.hpp"

fieldtrip::Client::Client()
{
}

void fieldtrip::Client::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

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

void fieldtrip::Client::sendHeader(const BufferParameters& parameters, std::vector<HeaderChunk> chunkList)
{

  (void)parameters;
  (void)chunkList;
}

void fieldtrip::Client::sendData(SharedPointer<Data> data)
{
  //to do: implement
  (void)data;
}

bool fieldtrip::Client::isConnected() const
{
  return mSocket.isConnected();
}

messagedef_t fieldtrip::Client::getResponse()
{
  std::string bufferResponseString = mSocket.receive_blocking();

  char* response_byte_array = new char[bufferResponseString.size()];
  memcpy(response_byte_array, bufferResponseString.c_str(), bufferResponseString.size());
  messagedef_t* bufferResponse = reinterpret_cast<messagedef_t*>(response_byte_array);

  return *bufferResponse;
}
