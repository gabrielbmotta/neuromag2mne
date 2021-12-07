//
// Created by Gabriel Motta on 12/2/21.
//

#include "ftdata.hpp"

size_t fieldtrip::FtData::size() const
{
  return mByteArray.size();
}

void* fieldtrip::FtData::data() const
{
  return mByteArray.data();
}
