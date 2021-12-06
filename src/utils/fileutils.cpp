#include "fileutils.hpp"

#include <fstream>
#include <iostream>

//==============================================================================
// Public API
//==============================================================================

bool FileUtils::fileExists(const std::string &filename)
{
  std::ifstream file(filename.c_str(), std::ios::binary);
  if(!file){
    std::cout << "FileUtils::size: Could not open file: " << filename << std::endl;
    return false;
  }
  return true;
}

size_t FileUtils::size(const std::string& filePath)
{
  if(fileExists(filePath)){
    std::ifstream file(filePath.c_str(), std::ios::binary);
    file.seekg(0, std::ios::end);
    if(file.tellg() >= 0)
      return static_cast<size_t>(file.tellg());
  }
  std::cout << "Error: FileUtils::size() failed to get file size" << std::endl;
  return 0;
}

void FileUtils::fileToBuffer(const std::string &filePath,
                             void *buffer,
                             size_t size)
{

  std::ifstream in(filePath.c_str());
  in.read(static_cast<char*>(buffer), static_cast<std::streamsize>(size));
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
