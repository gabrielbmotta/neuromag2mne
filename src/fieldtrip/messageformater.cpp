//
// Created by Gabriel Motta on 11/12/21.
//

#include "messageformater.hpp"

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
  messagedef_t* message = new messagedef_t();
  message->version = VERSION;
  message->bufsize = sizeof(headerdef_t);
  message->command = PUT_HDR;

  headerdef_t* header = new headerdef_t();
  header->nchans = parameters.nChannels;
  header->nsamples = 0;
  header->nevents = 0;
  header->fsample = parameters.sampleFrequency;
  header->data_type = parameters.dataType;
  header->bufsize = 0;

  size_t const totalSize = sizeof (messagedef_t) + sizeof (headerdef_t);

//  std::cout << "Total size : " << totalSize << "\n";
//  std::cout << "Message size : " << sizeof (messagedef_t) << "\n";
//  std::cout << "Header size : " << sizeof (headerdef_t) << "\n";

  char* messageByteArray = new char[totalSize];
  memcpy(messageByteArray, message, sizeof (messagedef_t));
  memcpy(messageByteArray + sizeof (messagedef_t), header, sizeof (headerdef_t));

  return fieldtrip::Message(messageByteArray, totalSize);
}

fieldtrip::Message fieldtrip::MessageFormater::neuromagHeader(fieldtrip::BufferParameters parameters,
                                                              std::string neuromagHeaderPath,
                                                              std::string isotrakHeaderPath)
{
  (void)parameters;
  (void)neuromagHeaderPath;
  (void)isotrakHeaderPath;

  return fieldtrip::Message();
}
