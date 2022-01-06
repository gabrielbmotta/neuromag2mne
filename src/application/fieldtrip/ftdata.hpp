#ifndef NEUROMAG2MNE_FTDATA_HPP
#define NEUROMAG2MNE_FTDATA_HPP

#include "fieldtriptypes.hpp"
#include "application/utils/bytearray.hpp"

namespace fieldtrip {

class FtData {
public:
  size_t size() const;
  void *data() const;

private:
  void setDataDef(const datadef_t &def);

  ByteArray mByteArray;
};
} // namespace fieldtrip
#endif //NEUROMAG2MNE_FTDATA_HPP
