//
// Created by Gabriel Motta on 12/2/21.
//

#ifndef NEUROMAG2MNE_BYTEARRAY_HPP
#define NEUROMAG2MNE_BYTEARRAY_HPP


class ByteArray {
public:
  ByteArray();
  ByteArray(const ByteArray&);
  ~ByteArray();
  ByteArray& operator=(const ByteArray&);

  void* data();
  size_t size();

private:
  char* mData;
  size_t mSize;
};


#endif //NEUROMAG2MNE_BYTEARRAY_HPP
