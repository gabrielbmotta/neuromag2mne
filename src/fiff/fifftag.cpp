#include "fifftag.hpp"


fiff::Tag::Tag()
{
  kind = 0;
  type = 0;
  size = 0;
  next = 0;
  data = NULL;
}

fiff::Tag::~Tag()
{
  if (data)
    delete [] static_cast<char *>(data);
}

fiff::Tag &fiff::Tag::operator=(const fiff::Tag &rhs)
{
  if(this == &rhs)
    return *this;

  kind = rhs.kind;
  type = rhs.type;
  size = rhs.size;
  next = rhs.next;

  char* temp_data = NULL;

  if(rhs.data && rhs.size > 0)
  {
    temp_data = new char[size];
    memcpy(temp_data, rhs.data, static_cast<size_t>(rhs.size));
  }

  if(data)
  {
    delete [] (static_cast<char *>(data));
  }
  data = temp_data;

  return *this;
}

