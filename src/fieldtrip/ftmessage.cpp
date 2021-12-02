#include "ftmessage.hpp"
#include <fstream>
#include "../utils/fileutils.hpp"
#include <iostream>

fieldtrip::FtMessage::FtMessage()
: mMessageByteArray(NULL)
, mSize(0)
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

static fieldtrip::FtMessage fieldtrip::FtMessageFormater::headerMessage(const Header& header)
{
  fieldtrip::FtMessage message;
  message.mByteArray.resize(header.mSize() + sizeof (messagedef_t))

  messagedef_t message_def = putHeaderMessagedef();

  memcpy(message.data(), &message_def, sizeof (messagedef_t));
  memcpy(message.data() + (sizeof message_def), &header, header.mSize());

  return message;
}

static fieldtrip::FtMessage fieldtrip::FtMessageFormater::dataMessage(const Data& data)
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

/*
Appends a byte array chunk with while keeping track of the mSize of data appended.
*/
void fieldtrip::FtMessageFormater::appendHeaderChunk(void *messageByteArray,
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

//==============================================================================
// Not to be used
//==============================================================================

/*
Set to private - not intended to be used and '= delete' is c++11.
*/
fieldtrip::FtMessageFormater::FtMessageFormater()
{
}
