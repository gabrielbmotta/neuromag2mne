#include "ftmessage.hpp"
#include <fstream>
#include "../utils/fileutils.hpp"
#include <iostream>
#include <cstring>

fieldtrip::FtMessage::FtMessage()
: mByteArray()
{
}

size_t fieldtrip::FtMessage::size() const
{
  return mByteArray.size();
}

void *fieldtrip::FtMessage::data() const
{
  return mByteArray.data();
}

fieldtrip::FtMessage fieldtrip::FtMessageFormater::headerMessage(const fieldtrip::FtHeader& header)
{
  fieldtrip::FtMessage message;
  message.mByteArray.resize(header.size() + sizeof (messagedef_t));

  messagedef_t message_def = putHeaderMessagedef();

  memcpy(message.data(), &message_def, sizeof (messagedef_t));
  memcpy(static_cast<char*>(message.data()) + sizeof (messagedef_t), &header, header.size());

  return message;
}

fieldtrip::FtMessage fieldtrip::FtMessageFormater::dataMessage(const FtData& data)
{
  (void)data;
  return fieldtrip::FtMessage();
}

/*
Creates a messagedef for putting a header in a buffer.
*/
messagedef_t fieldtrip::FtMessageFormater::putHeaderMessagedef()
{
  messagedef_t message;
  message.command = PUT_HDR;

  return message;
}

/*
Creates a messagedef for putting data in a buffer.
*/
messagedef_t fieldtrip::FtMessageFormater::putDataMessagedef()
{
  messagedef_t message;
  message.command = PUT_DAT;

  return message;
}

datadef_t fieldtrip::FtMessageFormater::datadefFromParam(fieldtrip::BufferParameters parameters)
{
  datadef_t data;

  data.nchans = parameters.nChannels;
  data.data_type = parameters.dataType;

  return data;
}

//==============================================================================
// Not to be used
//==============================================================================

/*
Set to private - not intended to be used and '= delete' is c++11.
*/
fieldtrip::FtMessageFormater::FtMessageFormater()
{
}
