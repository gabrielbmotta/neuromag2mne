#ifndef NEUROMAG2MNE_FILEUTILS_HPP
#define NEUROMAG2MNE_FILEUTILS_HPP

#include <string>

class FileUtils {
public:
  static long int size(const std::string& filePath);
  static void fileToBuffer(const std::string& filePath,
                           char* buffer,
                           size_t size);

private:
  FileUtils();
};

#endif //NEUROMAG2MNE_FILEUTILS_HPP
