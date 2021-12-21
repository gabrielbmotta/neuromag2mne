#include "fifftag.hpp"


fiff::Tag::Tag()
{
  kind = 0;
  type = 0;
  size = 0;
  next = 0;
  data = NULL;
}

fiff::Tag::Tag(const fiff::Tag& other)
{
  kind = other.kind;
  type = other.type;
  size = other.size;
  next = other.next;

  if(other.data && other.size > 0)
  {
    data = new char[size];
    memcpy(data, other.data, static_cast<size_t>(other.size));
  } else {
    data = NULL;
  }
}

fiff::Tag::~Tag()
{
  if (data)
  {
    delete[] static_cast<char *>(data);
  }
}

fiff::Tag &fiff::Tag::operator=(const fiff::Tag &rhs)
{
  if(this != &rhs)
  {
    kind = rhs.kind;
    type = rhs.type;
    size = rhs.size;
    next = rhs.next;

    if(rhs.data && rhs.size > 0)
    {
      if(data)
      {
        delete[] (static_cast<char *>(data));
      }
      data = new char[size];
      memcpy(data, rhs.data, static_cast<size_t>(rhs.size));
    }
  }
  return *this;
}

fiff::Tag fiff::samplingFrequencyTag(float samplingFrequency)
{
  fiff::Tag tag;
  tag.kind = FIFF_SFREQ;
  tag.type = FIFFT_FLOAT;
  tag.size = 4;
  tag.data = new char[tag.size];
  memcpy(tag.data, &samplingFrequency, static_cast<size_t>(tag.size));
  return tag;
}

fiff::Tag fiff::numberOfChannelsTag(int32_t numberOfChannels)
{
  fiff::Tag tag;
  tag.kind = FIFF_NCHAN;
  tag.type = FIFFT_INT;
  tag.size = 4;
  tag.data = new char[tag.size];
  memcpy(tag.data, &numberOfChannels, static_cast<size_t>(tag.size));
  return tag;
}
