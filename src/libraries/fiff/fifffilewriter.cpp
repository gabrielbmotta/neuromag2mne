#include "fifffilewriter.hpp"

fiff::FileWriter::FileWriter()
{

}

fiff::FileWriter::FileWriter(const std::string& filePath)
{
  open(filePath);
}

void fiff::FileWriter::open(const std::string& filePath)
{
  mFileOut.open(filePath.c_str(), std::ios::binary);
}

void fiff::FileWriter::close()
{
  mFileOut.close();
}

bool fiff::FileWriter::isOpen() const
{
  return mFileOut.is_open();
}

void fiff::FileWriter::writeTag(const fiff::Tag& tag)
{
  mFileOut.write(reinterpret_cast<const char*>(&tag.kind), sizeof (tag.kind));
  mFileOut.write(reinterpret_cast<const char*>(&tag.type), sizeof (tag.type));
  mFileOut.write(reinterpret_cast<const char*>(&tag.size), sizeof (tag.size));
  mFileOut.write(reinterpret_cast<const char*>(&tag.next), sizeof (tag.next));
  mFileOut.write(reinterpret_cast<const char*>(tag.data), tag.size);
}
