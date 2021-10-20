#ifndef NEUROMAG2MNE_STRINGCALLBACKPAIR_H
#define NEUROMAG2MNE_STRINGCALLBACKPAIR_H

struct StringCallbackPair
{
    StringCallbackPair(const std::string& s, void(*fcn)(void*), void* call)
            : trigger_string(s),
              callback(fcn),
              objPtr(call)
    {  };
    bool operator==(const StringCallbackPair& other) const;
    std::string trigger_string;
    void(*callback)(void*);
    void* objPtr;
};

#endif //NEUROMAG2MNE_STRINGCALLBACKPAIR_H
