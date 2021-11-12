//
// Created by Gabriel Motta on 11/12/21.
//

#include "fileutils.hpp"

#include <fstream>

long int FileUtils::qsize(const std::string& filePath)
{
  std::ifstream file(filePath, std::ios::binary);
  file.seekg(0,std::ios::end);
  return static_cast<long int>(file.tellg());
}

FileUtils::FileUtils()
{
}
