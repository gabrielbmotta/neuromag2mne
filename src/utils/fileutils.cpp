#include "fileutils.hpp"

#include <fstream>
#include <iostream>

//==============================================================================
// Public API
//==============================================================================

size_t FileUtils::size(const std::string& filePath)
{
  std::ifstream file(filePath.c_str(), std::ios::binary);
  file.seekg(0, std::ios::end);
  if(file.tellg() < 0)
    return 0;
  else
    return static_cast<size_t>(file.tellg());
}

void FileUtils::fileToBuffer(const std::string &filePath,
                             char *buffer,
                             size_t size)
{

  std::ifstream in(filePath.c_str());
  in.read(buffer, static_cast<std::streamsize>(size));
}

ByteArray FileUtils::getByteArrayFromFile(const std::string &path)
{
  size_t fileSize = FileUtils::size(path);

  if(fileSize == 0)
  {
    return ByteArray();
  }
  ByteArray byteArray(fileSize);
  FileUtils::fileToBuffer(path, byteArray.data(), fileSize);

  return byteArray;
}

//==============================================================================
// Not to be used
//==============================================================================

/*
Set to private - not intended to be used and '= delete' is c++11.
*/
FileUtils::FileUtils()
{
}
