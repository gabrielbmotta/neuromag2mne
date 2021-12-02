#ifndef NEUROMAG2MNE_BYTEARRAY_HPP
#define NEUROMAG2MNE_BYTEARRAY_HPP

#include <stddef.h>
#include <stdint.h>

class ByteArray {
public:
  ByteArray();
  explicit ByteArray(size_t size);
  ByteArray(const ByteArray&);
  ~ByteArray();
  ByteArray& operator=(const ByteArray&);

  void clear();
  void resize(size_t size);

  uint8_t* data() const;
  size_t size() const;
private:
  uint8_t* mData;
  size_t mSize;
};


#endif //NEUROMAG2MNE_BYTEARRAY_HPP
