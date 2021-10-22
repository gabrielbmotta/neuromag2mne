#ifndef NEUROMAG2MNE_STRINGCALLBACKPAIR_HPP
#define NEUROMAG2MNE_STRINGCALLBACKPAIR_HPP

#include <string>

template<typename T>
class StringCallbackPair
{
public:
  typedef void (T::*memberT)();
  StringCallbackPair(const std::string& s, memberT fcn, T* t)
  :trigger_string(s),mFcn(fcn), m(t){}

  bool operator==(const StringCallbackPair& other) const
  {
    return ( trigger_string == other.trigger_string ) &&
           ( mFcn == other.mFcn ) &&
           ( m == other.m );
  }
  void operator()(){
    (m->*mFcn)();
  }
  void callCallback()
  {
    (m->*mFcn)();
  }
  std::string& string()
  {
    return trigger_string;
  }
  memberT& callbackName()
  {
    return mFcn;
  }
private:
  std::string trigger_string;
  memberT mFcn;
  T* m;
};

#endif //NEUROMAG2MNE_STRINGCALLBACKPAIR_HPP
