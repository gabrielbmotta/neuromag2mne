#ifndef NEUROMAG2MNE_FILEUTILS_HPP
#define NEUROMAG2MNE_FILEUTILS_HPP

#include <string>
#include "bytearray.hpp"

class FileUtils {
public:
  static size_t size(const std::string& filePath);
  static void fileToBuffer(const std::string& filePath,
                           char* buffer,
                           size_t size);

  static ByteArray getByteArrayFromFile(const std::string& path);


private:
  FileUtils();
};

#endif //NEUROMAG2MNE_FILEUTILS_HPP
