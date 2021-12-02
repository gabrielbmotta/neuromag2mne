//
// Created by Gabriel Motta on 12/2/21.
//

#include "bytearray.hpp"

ByteArray::ByteArray()
:
{

}

ByteArray::ByteArray(const ByteArray &)
{

}

ByteArray::~ByteArray()
{

}

ByteArray &ByteArray::operator=(const ByteArray &)
{
  return <#initializer#>;
}

void *ByteArray::data()
{
  return static_cast<void*>mData;
}

size_t ByteArray::size()
{
  return mSize;
}
