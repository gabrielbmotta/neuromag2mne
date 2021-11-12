#ifndef NEUROMAG2MNE_FILEUTILS_HPP
#define NEUROMAG2MNE_FILEUTILS_HPP

#include <string>

class FileUtils {
public:
  static long int size(const std::string& filePath);

private:
  FileUtils();
};

#endif //NEUROMAG2MNE_FILEUTILS_HPP
