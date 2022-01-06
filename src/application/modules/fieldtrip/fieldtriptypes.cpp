#include "fieldtriptypes.hpp"

fieldtrip::datadef_t::datadef_t()
        : nchans(0)
        , nsamples(0)
        , data_type(0)
        , bufsize(0)
{
}

fieldtrip::headerdef_t::headerdef_t()
: nchans(0)
, nsamples(0)
, nevents(0)
, fsample(0)
, data_type(0)
, bufsize(0)
{
}

fieldtrip::chunkdef_t::chunkdef_t()
: type(0)
, size(0)
{
}

fieldtrip::chunkdef_t::chunkdef_t(int32_t chunkType, int32_t chunkSize)
: type(chunkType)
, size(chunkSize)
{
}

fieldtrip::messagedef_t::messagedef_t()
: version(VERSION)
, command(0)
, bufsize(0)
{
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putHeader()
{
  messagedef_t message;
  message.command = PUT_HDR;
  return message;
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putHeader(int32_t headerSize)
{
  messagedef_t header = putHeader();
  header.bufsize = headerSize;
  return header;
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putHeader(size_t headerSize)
{
  return fieldtrip::messagedef_t::putHeader(static_cast<int32_t>(headerSize));
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putData()
{
  messagedef_t message;
  message.command = PUT_DAT;
  return message;
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putData(int32_t dataSize)
{
  messagedef_t message = putData();
  message.bufsize = dataSize;
  return message;
}

fieldtrip::messagedef_t fieldtrip::messagedef_t::putData(size_t dataSize)
{
  return fieldtrip::messagedef_t::putData(static_cast<int32_t>(dataSize));
}

fieldtrip::BufferParameters::BufferParameters(int channels, float frequency, int type)
: mNumChannels(channels)
, mSampleFrequency(frequency)
, mDataType(type)
{
}

fieldtrip::headerdef_t fieldtrip::BufferParameters::generateHeaderdef() const
{
  headerdef_t headerdef;

  headerdef.nchans = mNumChannels;
  headerdef.fsample = mSampleFrequency;
  headerdef.data_type = mDataType;

  return headerdef;
}

fieldtrip::datadef_t fieldtrip::BufferParameters::generateDatadef() const
{
  datadef_t data;

  data.nchans = mNumChannels;
  data.data_type = mDataType;

  return data;
}


