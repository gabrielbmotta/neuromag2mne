#ifndef NEUROMAG2MNE_FILEUTILS_HPP
#define NEUROMAG2MNE_FILEUTILS_HPP

#include <string>
#include <cstring>
#include "bytearray.hpp"

class FileUtils {
public:
  static bool fileExists(const std::string& filename);

  static size_t size(const std::string& filePath);

  static void fileToBuffer(const std::string& filePath,
                           void* buffer,
                           size_t size);

  static ByteArray readFromFile(const std::string& path);

private:
  FileUtils();
};

#endif //NEUROMAG2MNE_FILEUTILS_HPP
