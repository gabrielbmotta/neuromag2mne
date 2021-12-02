//
// Created by Gabriel Motta on 12/2/21.
//

#include "bytearray.hpp"
#include <iostream>

ByteArray::ByteArray()
: mData(NULL)
, mSize(0)
{
}

ByteArray::ByteArray(size_t size)
: mData(new char[size])
, mSize(size)
{
}

ByteArray::ByteArray(const ByteArray &other)
{
    mSize = other.mSize;
    mData = new char[mSize];
    memcpy(mData, other.mData, mSize);
}

ByteArray::~ByteArray()
{
  clear();
}

ByteArray &ByteArray::operator=(const ByteArray &rhs)
{
    if (this != &rhs){
      clear();
      if(rhs.mData){
        mData = new char[rhs.mSize];
        memcpy(mData, rhs.mData, rhs.mSize);
        mSize = rhs.mSize;
      }
    }
    return *this;
}

void ByteArray::clear()
{
  if(mData){
    delete[] mData;
    mData = NULL;
    mSize = 0;
  }
}

void *ByteArray::data() const
{
  return static_cast<void*>(mData);
}

size_t ByteArray::size() const
{
  return mSize;
}

void ByteArray::resize(size_t size)
{
  clear();
  mData = new char[size];
  mSize = size;
}

