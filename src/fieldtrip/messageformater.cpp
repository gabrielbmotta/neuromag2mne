//
// Created by Gabriel Motta on 11/12/21.
//

#include "messageformater.hpp"
#include <fstream>
#include "../utils/fileutils.hpp"

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
  char* neuromagByteArray = getDataFromFile(neuromagHeaderPath);
  char* isotrakByteArray = getDataFromFile(isotrakHeaderPath);
  if(neuromagByteArray == NULL || isotrakByteArray == NULL){
    return fieldtrip::Message();
  }
  size_t totalChunkSize = sizeof (neuromagByteArray) + sizeof (isotrakByteArray);

  messagedef_t* message = putHeaderMessage();
  headerdef_t* header = defaultHeader();

  header->nchans = parameters.nChannels;
  header->fsample = parameters.sampleFrequency;
  header->data_type = parameters.dataType;
  header->bufsize = static_cast<int>(totalChunkSize);

  message->bufsize = static_cast<int>(sizeof (headerdef_t) + totalChunkSize);

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t) + totalChunkSize;
  char* messageByteArray = new char[totalSize];


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

char* fieldtrip::MessageFormater::getDataFromFile(const std::string& path)
{
  long int fileSize = FileUtils::size(path);
  if (fileSize < 0){
    return NULL;
  }
  char* buffer = new char[fileSize];
  FileUtils::fileToBuffer(path,buffer,static_cast<size_t>(fileSize));
  return buffer;
}

fieldtrip::MessageFormater::MessageFormater()
{
}
