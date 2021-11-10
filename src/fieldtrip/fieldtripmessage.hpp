#ifndef NEUROMAG2MNE_FIELDTRIPMESSAGE_HPP
#define NEUROMAG2MNE_FIELDTRIPMESSAGE_HPP

#include "fieldtriptypes.hpp"

class FieldTripMessage {
  static message_t* headerSimple(BufferParameters);
  static message_t* headerWithChunks(BufferParameters);


};


#endif //NEUROMAG2MNE_FIELDTRIPMESSAGE_HPP
