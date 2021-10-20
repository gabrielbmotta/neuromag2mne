#include "stringcallbackpair.h"

StringCallbackPair::StringCallbackPair(const std::string& s, void (*fcn)(void *), void *call)
        : trigger_string(s),
          callback(fcn),
          objPtr(call)
{  };

bool StringCallbackPair::operator==(const StringCallbackPair& other) const
{
  return (trigger_string == other.trigger_string) && (callback == other.callback);
}
