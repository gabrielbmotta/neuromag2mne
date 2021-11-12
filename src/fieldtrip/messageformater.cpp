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
  long int neuromagHeaderFileSize = FileUtils::size(neuromagHeaderPath);
  long int isotrakHeaderFileSize = FileUtils::size(isotrakHeaderPath);
  if(neuromagHeaderFileSize == -1 || isotrakHeaderFileSize == -1)
  {
    return fieldtrip::Message();
  }

  (void)parameters;

  return fieldtrip::Message();
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

fieldtrip::MessageFormater::MessageFormater()
{
}
