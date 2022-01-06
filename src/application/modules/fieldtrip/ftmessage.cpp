#include "ftmessage.hpp"
#include <fstream>
#include "utils/fileutils.hpp"
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

fieldtrip::FtMessage fieldtrip::FtMessage::headerMessage(const fieldtrip::FtHeader& header)
{
  fieldtrip::FtMessage message;
  if(header.size() > 0)
  {
    message.mByteArray.resize(header.size() + sizeof(messagedef_t));
    message.setMessageDef(messagedef_t::putHeader(header.size()));
    message.setMessageContent(header.data(), header.size());
  }
  return message;
}

fieldtrip::FtMessage fieldtrip::FtMessage::dataMessage(const FtData& data)
{
  fieldtrip::FtMessage message;
  if(data.size() > 0)
  {
    message.mByteArray.resize(data.size() + sizeof(messagedef_t));
    message.setMessageDef(messagedef_t::putData(data.size()));
    message.setMessageContent(data.data(), data.size());
  }
  return message;
}

void fieldtrip::FtMessage::setMessageDef(const fieldtrip::messagedef_t &messagedef)
{
  if(size() >= sizeof (messagedef_t))
  {
    *(reinterpret_cast<messagedef_t *>(data())) = messagedef;
  }
}

void fieldtrip::FtMessage::setMessageContent(const void *data, size_t size)
{
  memcpy(mByteArray.data() + sizeof(messagedef_t), data, size);
}
