#include "ftclient.hpp"


fieldtrip::Client::Client()
{
}

void fieldtrip::Client::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

void fieldtrip::Client::sendHeader(const BufferParameters& param)
{
  //to do: implement
  (void)param;
  header_t* header = NULL;
  formatHeader(header, param);

  message_t* message = NULL;

  message = new message_t();
  message->def = new messagedef_t();
  message->buf = NULL;
  message->def->version = VERSION;
  message->def->bufsize = 0;
  message->def->command = PUT_HDR;


}

void fieldtrip::Client::sendHeader(const BufferParameters& param, std::vector<HeaderChunk> chunkList)
{

  (void)param;
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
