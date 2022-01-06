//
// Created by Gabriel Motta on 12/2/21.
//

#include "bytearray.hpp"
#include <iostream>
#include <cstring>

ByteArray::ByteArray()
: mData(NULL)
, mSize(0)
{
}

ByteArray::ByteArray(size_t size)
: mData(new uint8_t[size])
, mSize(size)
{
}

ByteArray::ByteArray(const ByteArray &other)
{
    mSize = other.mSize;
    mData = new uint8_t[mSize];
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
        mData = new uint8_t[rhs.mSize];
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

uint8_t *ByteArray::data() const
{
  return mData;
}

size_t ByteArray::size() const
{
  return mSize;
}

void ByteArray::resize(size_t size)
{
  clear();
  mData = new uint8_t[size];
  mSize = size;
}

uint8_t &ByteArray::operator[](size_t index)
{
  return mData[index];
}

const uint8_t &ByteArray::operator[](size_t index) const
{
  return mData[index];
}

