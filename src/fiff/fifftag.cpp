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
  if(this == &rhs)
    return *this;

  kind = rhs.kind;
  type = rhs.type;
  size = rhs.size;
  next = rhs.next;

  if(rhs.data && rhs.size > 0)
  {
    if(data)
    {
      delete [] (static_cast<char *>(data));
    }
    data = new char[size];
    memcpy(data, rhs.data, static_cast<size_t>(rhs.size));
  }

  return *this;
}

