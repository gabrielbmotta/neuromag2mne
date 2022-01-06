#ifndef NEUROMAG2MNE_FIFFFILEREADER_HPP
#define NEUROMAG2MNE_FIFFFILEREADER_HPP

#include <fstream>
#include <string>
#include "libraries/fiff/fifftag.hpp"

namespace fiff {
class FileReader {
public:
  FileReader();
  explicit FileReader(const std::string &filename);

  void open(const std::string &filename);
  void close();
  bool isOpen() const;

  Tag readNextTag();
  Tag peekNextTag();

  bool isAtEnd() const;

private:
  std::ifstream mFileIn;

};

} // namespace fiff
#endif //NEUROMAG2MNE_FIFFFILEREADER_HPP
