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
  messagedef_t* message = putHeaderMessage();
  message->bufsize = sizeof(headerdef_t);

  headerdef_t* header = defaultHeader();
  header->nchans = parameters.nChannels;
  header->fsample = parameters.sampleFrequency;
  header->data_type = parameters.dataType;

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t);
  char* messageByteArray = new char[totalSize];

  memcpy(messageByteArray, message, sizeof (messagedef_t));
  memcpy(messageByteArray + sizeof (messagedef_t), header, sizeof (headerdef_t));

  return fieldtrip::Message(messageByteArray, totalSize);
}

fieldtrip::Message fieldtrip::MessageFormater::neuromagHeader(fieldtrip::BufferParameters parameters,
                                                              const std::string& neuromagHeaderPath,
                                                              const std::string& isotrakHeaderPath)
{
  std::pair<char*, long> neuromagByteArray = getDataFromFile(neuromagHeaderPath);
  std::pair<char*, long> isotrakByteArray = getDataFromFile(isotrakHeaderPath);
  if(neuromagByteArray.first == NULL || isotrakByteArray.first == NULL){
    std::cout << "Unable to attatch files as headers.\n";
    return fieldtrip::Message();
  }
  size_t totalChunkSize = neuromagByteArray.second + isotrakByteArray.second + 2 * sizeof (chunkdef_t);

  std::cout << "Total size of chunks: " << totalChunkSize << "\n";
  messagedef_t* message = putHeaderMessage();
  headerdef_t* header = defaultHeader();

  header->nchans = parameters.nChannels;
  header->fsample = parameters.sampleFrequency;
  header->data_type = parameters.dataType;
  header->bufsize = static_cast<int>(totalChunkSize);

  message->bufsize = static_cast<int>(sizeof (headerdef_t) + totalChunkSize);

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t) + totalChunkSize;
  char* messageByteArray = new char[totalSize];

  size_t offset = 0;
  //Standard message and header
  memcpy(messageByteArray + offset, message, sizeof (messagedef_t));
  offset += sizeof (messagedef_t);
  memcpy(messageByteArray + offset, header, sizeof (headerdef_t));
  offset += sizeof (headerdef_t);
  
  //Neuromag header chunk
  chunkdef_t neuromagdef;
  neuromagdef.type = 8;
  neuromagdef.size = static_cast<int>(neuromagByteArray.second);
  memcpy(messageByteArray + offset, &neuromagdef, sizeof(chunkdef_t));
  offset += sizeof(chunkdef_t); 
  memcpy(messageByteArray + offset, neuromagByteArray.first, neuromagByteArray.second);
  offset += neuromagByteArray.second;

  //Isotrak header chunk
  chunkdef_t isotrakdef;
  isotrakdef.type = 9;
  isotrakdef.size = static_cast<int>(isotrakByteArray.second);
  memcpy(messageByteArray + offset, &isotrakdef, sizeof(chunkdef_t));
  offset += sizeof(chunkdef_t); 
  memcpy(messageByteArray + offset, isotrakByteArray.first, isotrakByteArray.second);
  offset += isotrakByteArray.second;

  return fieldtrip::Message(messageByteArray, totalSize);
}

messagedef_t* fieldtrip::MessageFormater::putHeaderMessage()
{
  messagedef_t* message = new messagedef_t();
  message->version = VERSION;
  message->bufsize = 0;
  message->command = PUT_HDR;

  return message;
}

messagedef_t* fieldtrip::MessageFormater::putDataMessage()
{
  messagedef_t* message = new messagedef_t();
  message->version = VERSION;
  message->bufsize = 0;
  message->command = PUT_DAT;

  return message;
}

headerdef_t* fieldtrip::MessageFormater::defaultHeader()
{
  headerdef_t* header = new headerdef_t();
  header->nchans = 0;
  header->nsamples = 0;
  header->nevents = 0;
  header->fsample = 0;
  header->data_type = 0;
  header->bufsize = 0;

  return header;
}

std::pair<char*, long> fieldtrip::MessageFormater::getDataFromFile(const std::string& path)
{
  long int fileSize = FileUtils::size(path);
  if (fileSize < 0){
    return std::pair<char*, long>(NULL,0);
  }
  char* buffer = new char[fileSize];
  FileUtils::fileToBuffer(path,buffer,static_cast<size_t>(fileSize));
  return std::pair<char*, long>(buffer, fileSize);
}

fieldtrip::MessageFormater::MessageFormater()
{
}
