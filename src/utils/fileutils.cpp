#include "fileutils.hpp"

#include <fstream>
#include <iostream>

long int FileUtils::size(const std::string& filePath)
{
  std::ifstream file(filePath.c_str(), std::ios::binary);
  file.seekg(0,std::ios::end);
  return static_cast<long int>(file.tellg());
}

void FileUtils::fileToBuffer(const std::string &filePath,
                             char *buffer,
                             size_t size)
{

  std::ifstream in(filePath.c_str());
  in.read(buffer, static_cast<std::streamsize>(size));
}

FileUtils::FileUtils()
{
}


