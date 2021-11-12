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

  std::string response = mSocket.receive_blocking();

  char* response_byte_array = new char[response.size()];
  memcpy(response_byte_array, response.c_str(), response.size());
  messagedef_t* resp = reinterpret_cast<messagedef_t*>(response_byte_array);

  std::cout << "Response: " << resp->command;
}

void fieldtrip::Client::sendHeader(const BufferParameters& parameters, std::vector<HeaderChunk> chunkList)
{

  (void)parameters;
  for(size_t i = 0; i < chunkList.size(); ++i )
  {
    sendHeaderChunk(chunkList[i]);
  }
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

void fieldtrip::Client::sendHeaderChunk(HeaderChunk chunk)
{
  //to do: implement
  (void)chunk;
}

void fieldtrip::Client::formatHeader(header_t *header, const BufferParameters& param) const
{
  header = new header_t();
  header->def = new headerdef_t();

  header->def->nchans = param.nChannels;
  header->def->nsamples = 0;
  header->def->nevents = 0;
  header->def->fsample = param.sampleFrequency;
  header->def->data_type = param.dataType;
  header->def->bufsize = 0;
  header->buf = NULL;
}
