#include "ftclient.hpp"
#include <cstring>
#include <iostream>


fieldtrip::Client::Client()
{
}

void fieldtrip::Client::connect(std::string address, unsigned short port)
{
  mSocket.connect(address, port);
}

void fieldtrip::Client::sendHeader(const BufferParameters& param)
{
  if(!mSocket.isConnected()){
    return;
  }

  std::cout << "1\n";

  //to do: implement
  (void)param;
  header_t* header = new header_t();
  header->def = new headerdef_t();

  header->def->nchans = param.nChannels;
  header->def->nsamples = 0;
  header->def->nevents = 0;
  header->def->fsample = param.sampleFrequency;
  header->def->data_type = param.dataType;
  header->def->bufsize = 0;
  header->buf = NULL;

  message_t* message = NULL;

  std::cout << "2\n";

  message = new message_t();
  message->def = new messagedef_t();
  message->buf = NULL;
  message->def->version = VERSION;
  message->def->bufsize = sizeof(headerdef_t);
  message->def->command = PUT_HDR;

  std::cout << "3\n";

  int const totalMessageSize = sizeof (messagedef_t) + sizeof (headerdef_t);


  std::cout << "Total size : " << totalMessageSize << "\n";
  std::cout << "Message size : " << sizeof (messagedef_t) << "\n";

  std::cout << "Header size : " << sizeof (headerdef_t) << "\n";

  std::cout << "4\n";


  char* msg = new char[totalMessageSize];

  memcpy(msg, message->def, sizeof (messagedef_t));

  std::cout << "5\n";

  memcpy(msg + sizeof (messagedef_t), header->def, sizeof (headerdef_t));

  std::cout << "6\n";

  mSocket.send(msg, totalMessageSize);

  std::cout << "7\n";

  std::string response = mSocket.receive_blocking();

  char* response_byte_array = new char[response.size()];

  std::cout << "8\n";

  memcpy(response_byte_array, response.c_str(), response.size());

  messagedef_t* resp = reinterpret_cast<messagedef_t*>(response_byte_array);

  std::cout << "9\n";

  std::cout << "Response: " << resp->command;
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
