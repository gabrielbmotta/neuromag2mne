#include "fileutils.hpp"

#include <fstream>
#include <iostream>

//==============================================================================
// Public API
//==============================================================================

/*
Returns whether file at path exists. If using a relative path,
the call will be relative to the current working directory.
*/
bool FileUtils::fileExists(const std::string &filename)
{
  std::ifstream file(filename.c_str(), std::ios::binary);
  if(!file){
    std::cout << "FileUtils::size: Could not open file: " << filename << std::endl;
    return false;
  }
  return true;
}

/*
Returns the size of the file at path. If file does not exist this
will return zero. If using a relative path, the call will be relative
to the current working directory.
*/
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

/*
Reads the contents of the file at path to buffer variable.
This function expects a buffer that has been allocated the
correct size and a file that exists. If using a relative path,
the call will be relative to the current working directory.

Prefer using readFromFile instead of this function.
*/
void FileUtils::fileToBuffer(const std::string &filePath,
                             void *buffer,
                             size_t size)
{

  std::ifstream in(filePath.c_str());
  in.read(static_cast<char*>(buffer), static_cast<std::streamsize>(size));
}

/*
Returns a byte array of the contents of the file at path. Returns
empty byte array is file does not exist or is empty. If using a
relative path, the call will be relative to the current working
directory.
*/
ByteArray FileUtils::readFromFile(const std::string &path)
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
