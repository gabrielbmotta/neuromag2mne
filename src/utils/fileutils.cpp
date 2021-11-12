#include "fileutils.hpp"

#include <fstream>

long int FileUtils::size(const std::string& filePath)
{
  std::ifstream file(filePath.c_str(), std::ios::binary);
  file.seekg(0,std::ios::end);
  return static_cast<long int>(file.tellg());
}

FileUtils::FileUtils()
{
}
