#include "ftclient.hpp"


fieldtrip::Client::Client()
{
}

void fieldtrip::Client::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

void fieldtrip::Client::sendHeader(BufferParameters param)
{
  //to do: implement
  (void)param;
}

void fieldtrip::Client::sendHeader(BufferParameters param, std::vector<HeaderChunk> chunkList)
{
  sendHeader(param);
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
