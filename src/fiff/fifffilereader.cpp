#include "fifffilereader.hpp"


fiff::FileReader::FileReader()
{

}

fiff::FileReader::FileReader(const std::string &filename)
{
  open(filename);
}

void fiff::FileReader::open(const std::string &filename)
{
  mFileIn.open(filename.c_str(), std::ios::in | std::ios::binary);
}

void fiff::FileReader::close()
{
  mFileIn.close();
}

bool fiff::FileReader::isOpen() const
{
  return mFileIn.is_open();
}

fiff::Tag fiff::FileReader::readNextTag()
{
  fiff::Tag tag;

  mFileIn.read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  mFileIn.read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  mFileIn.read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  mFileIn.read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));
  tag.data = new char[tag.size];
  mFileIn.read(reinterpret_cast<char*>(tag.data), tag.size);

  return tag;
}

fiff::Tag fiff::FileReader::peekNextTag()
{
  std::streampos position = mFileIn.tellg();
  fiff::Tag tag = readNextTag();
  mFileIn.seekg(position);
  return tag;
}

bool fiff::FileReader::isAtEnd() const
{
  return mFileIn.eof();
}
