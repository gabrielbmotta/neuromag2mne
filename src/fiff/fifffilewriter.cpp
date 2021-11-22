#include "fifffilewriter.hpp"

fiff::FileWriter::FileWriter(std::string filePath)
{
  open(filePath);
}

void fiff::FileWriter::open(std::string filePath)
{
  mFileOut.open(filePath, std::ios::binary);
}

void fiff::FileWriter::close()
{
  mFileOut.close();
}

bool fiff::FileWriter::isOpen()
{
  return mFileOut.is_open();
}

void fiff::FileWriter::writeTag(fiff::Tag tag)
{
  (void)tag;
}
