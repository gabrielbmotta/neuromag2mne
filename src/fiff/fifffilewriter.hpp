#ifndef NEUROMAG2MNE_FIFFFILEWRITER_HPP
#define NEUROMAG2MNE_FIFFFILEWRITER_HPP

#include <string>
#include <fstream>
#include "fifftag.hpp"

namespace fiff {

class FileWriter {
public:
  FileWriter();
  FileWriter(const std::string& filePath);

  void open(const std::string& filePath);
  void close();
  bool isOpen() const;

  void writeTag(const fiff::Tag& tag);
private:
  std::ofstream mFileOut;
};
}//namespace
#endif //NEUROMAG2MNE_FIFFFILEWRITER_HPP
