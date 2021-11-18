#include "messageformater.hpp"
#include <fstream>
#include "../utils/fileutils.hpp"
#include <iostream>

fieldtrip::Message::Message()
: content(NULL)
, size(0)
{

}

fieldtrip::Message::Message(char *message_ptr,
                            size_t message_size)
: content(message_ptr)
, size(message_size)
{

}

void fieldtrip::Message::done()
{
  if (content != NULL){
    delete[] content;
  }
}

fieldtrip::Message fieldtrip::MessageFormater::simpleHeader(fieldtrip::BufferParameters parameters)
{
  messagedef_t message = putHeaderMessage();
  message.bufsize = sizeof(headerdef_t);

  headerdef_t header = headerFromParam(parameters);

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t);
  char* messageByteArray = new char[totalSize];

  memcpy(messageByteArray, &message, sizeof (messagedef_t));
  memcpy(messageByteArray + sizeof (messagedef_t), &header, sizeof (headerdef_t));

  return fieldtrip::Message(messageByteArray, totalSize);
}

fieldtrip::Message fieldtrip::MessageFormater::neuromagHeader(fieldtrip::BufferParameters parameters,
                                                              const std::string& neuromagHeaderPath,
                                                              const std::string& isotrakHeaderPath)
{
  std::pair<char*, size_t> neuromagByteArray = getDataFromFile(neuromagHeaderPath);
  std::pair<char*, size_t> isotrakByteArray = getDataFromFile(isotrakHeaderPath);
  if(neuromagByteArray.first == NULL || isotrakByteArray.first == NULL){
    std::cout << "Unable to attach files as headers. Returning simple header.\n";
    return simpleHeader(parameters);
  }
  size_t totalChunkSize = static_cast<size_t>(neuromagByteArray.second + isotrakByteArray.second + 2 * sizeof (chunkdef_t));

  messagedef_t message = putHeaderMessage();
  message.bufsize = static_cast<int>(sizeof (headerdef_t) + totalChunkSize);

  headerdef_t header = headerFromParam(parameters);
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

  return fieldtrip::Message(messageByteArray, totalSize);
}

messagedef_t fieldtrip::MessageFormater::putHeaderMessage()
{
  messagedef_t message;
  message.command = PUT_HDR;

  return message;
}

messagedef_t fieldtrip::MessageFormater::putDataMessage()
{
  messagedef_t message;
  message.command = PUT_DAT;

  return message;
}

headerdef_t fieldtrip::MessageFormater::headerFromParam(fieldtrip::BufferParameters parameters)
{
  headerdef_t header;

  header.nchans = parameters.nChannels;
  header.fsample = parameters.sampleFrequency;
  header.data_type = parameters.dataType;

  return header;
}

std::pair<char*, size_t> fieldtrip::MessageFormater::getDataFromFile(const std::string& path)
{
  long int fileSize = FileUtils::size(path);
  if (fileSize < 0){
    return std::pair<char*, size_t>(NULL,0);
  }
  char* buffer = new char[fileSize];
  FileUtils::fileToBuffer(path,buffer, static_cast<size_t>(fileSize));
  return std::pair<char*, size_t>(buffer, static_cast<size_t>(fileSize));
}

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

fieldtrip::MessageFormater::MessageFormater()
{
}
