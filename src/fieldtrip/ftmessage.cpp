#include "ftmessage.hpp"
#include <fstream>
#include "../utils/fileutils.hpp"
#include <iostream>

fieldtrip::FtMessage::FtMessage()
: mMessageByteArray(NULL)
, mSize(0)
{

}

fieldtrip::FtMessage::FtMessage(char *message_ptr,
                                size_t message_size)
: mMessageByteArray(message_ptr)
, mSize(message_size)
{

}
fieldtrip::FtMessage &fieldtrip::FtMessage::operator=(const fieldtrip::FtMessage &other)
{
  return <#initializer#>;
}

fieldtrip::FtMessage::FtMessage(const fieldtrip::FtMessage &other)
{

}

fieldtrip::FtMessage::~FtMessage()
{

}

static fieldtrip::FtMessage fieldtrip::MessageFormater::headerMessage(const Header& header)
{
  fieldtrip::FtMessage message;
  message.mSize = header.mSize() + sizeof (messagedef_t);
  message.mMessageByteArray = new char[message.mSize];

  messagedef_t message_def = putHeaderMessagedef();

  memcpy(message.mMessageByteArray, &message_def, sizeof (messagedef_t));
  memcpy(message.mMessageByteArray + (sizeof message_def), &header, header.mSize());

  return message;
}

static fieldtrip::FtMessage fieldtrip::MessageFormater::dataMessage(const Data& data)
{
return fieldtrip::FtMessage();
}

/*
Returns a messsage for setting a fieldtrip buffer header based on input buffer parameters.
*/
fieldtrip::FtMessage fieldtrip::MessageFormater::simpleHeader(const fieldtrip::BufferParameters& parameters)
{
  messagedef_t message = putHeaderMessagedef();
  message.bufsize = sizeof(headerdef_t);

  headerdef_t header = headerdefFromParam(parameters);

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t);
  char* messageByteArray = new char[totalSize];

  memcpy(messageByteArray, &message, sizeof (messagedef_t));
  memcpy(messageByteArray + sizeof (messagedef_t), &header, sizeof (headerdef_t));

  return fieldtrip::FtMessage(messageByteArray, totalSize);
}

/*
Returns a messsage for setting a fieldtrip buffer header based on input buffer parameters
and header chunk files.
*/
fieldtrip::FtMessage fieldtrip::MessageFormater::neuromagHeader(const fieldtrip::BufferParameters& parameters,
                                                                const std::string& neuromagHeaderPath,
                                                                const std::string& isotrakHeaderPath)
{
  std::pair<char*, size_t> neuromagByteArray = getByteArrayFromFile(neuromagHeaderPath);
  std::pair<char*, size_t> isotrakByteArray = getByteArrayFromFile(isotrakHeaderPath);
  if(neuromagByteArray.first == NULL || isotrakByteArray.first == NULL){
    std::cout << "Unable to attach files as headers. Returning simple header.\n";
    return simpleHeader(parameters);
  }
  size_t totalChunkSize = static_cast<size_t>(neuromagByteArray.second + isotrakByteArray.second + 2 * sizeof (chunkdef_t));

  messagedef_t message = putHeaderMessagedef();
  message.bufsize = static_cast<int>(sizeof (headerdef_t) + totalChunkSize);

  headerdef_t header = headerdefFromParam(parameters);
  header.bufsize = static_cast<int>(totalChunkSize);

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t) + totalChunkSize;
  char* messageByteArray = new char[totalSize];

  size_t offset = 0;
  memcpy(messageByteArray + offset, &message, sizeof (messagedef_t));
  offset += sizeof (messagedef_t);
  memcpy(messageByteArray + offset, &header, sizeof (headerdef_t));
  offset += sizeof (headerdef_t);

  appendHeaderChunk(messageByteArray, neuromagByteArray, 8, offset);
  appendHeaderChunk(messageByteArray, isotrakByteArray, 9, offset);

  return fieldtrip::FtMessage(messageByteArray, totalSize);
}

fieldtrip::FtMessage fieldtrip::MessageFormater::rawDataMessage(const fieldtrip::BufferParameters& parameters,
                                                                char* data,
                                                                size_t dataSize)
{
  messagedef_t messagedef = putDataMessagedef();
  messagedef.bufsize = static_cast<int>(dataSize + sizeof(datadef_t));

  datadef_t datadef = datadefFromParam(parameters);
  datadef.bufsize = static_cast<int>(dataSize);

  size_t totalSize = dataSize + sizeof(datadef_t) + sizeof(messagedef_t);
  char* messageByteArray = new char[totalSize];


  (void)messagedef;
  (void)datadef;
  (void)data;
  (void)messageByteArray;

  return FtMessage();
}

/*
Creates a messagedef for putting a header in a buffer.
*/
messagedef_t fieldtrip::MessageFormater::putHeaderMessagedef()
{
  messagedef_t message;
  message.command = PUT_HDR;

  return message;
}

/*
Creates a messagedef for putting data in a buffer.
*/
messagedef_t fieldtrip::MessageFormater::putDataMessagedef()
{
  messagedef_t message;
  message.command = PUT_DAT;

  return message;
}

datadef_t fieldtrip::MessageFormater::datadefFromParam(fieldtrip::BufferParameters parameters)
{
  datadef_t data;

  data.nchans = parameters.nChannels;
  data.data_type = parameters.dataType;

  return data;
}

/*
Gets data from a file and returns ina a pair of char* (array of data) and size_t (mSize of array)
*/
std::pair<char*, size_t> fieldtrip::MessageFormater::getByteArrayFromFile(const std::string& path)
{
  long int fileSize = FileUtils::size(path);
  if (fileSize < 0){
    return std::pair<char*, size_t>(NULL,0);
  }
  char* buffer = new char[fileSize];
  FileUtils::fileToBuffer(path,buffer, static_cast<size_t>(fileSize));
  return std::pair<char*, size_t>(buffer, static_cast<size_t>(fileSize));
}

/*
Appends a byte array chunk with while keeping track of the mSize of data appended.
*/
void fieldtrip::MessageFormater::appendHeaderChunk(char *messageByteArray,
                                                   std::pair<char *, size_t> &chunk,
                                                   int chunkID,
                                                   size_t &offset)
{
  chunkdef_t chunkdef;
  chunkdef.type = chunkID;
  chunkdef.size = static_cast<int>(chunk.second);
  memcpy(messageByteArray + offset, &chunkdef, sizeof(chunkdef_t));
  offset += sizeof(chunkdef_t);
  memcpy(messageByteArray + offset, chunk.first, chunk.second);
  offset += chunk.second;
}

/*
Set to private - not intended to be used and '= delete' is c++11.
*/
fieldtrip::MessageFormater::MessageFormater()
{
}
