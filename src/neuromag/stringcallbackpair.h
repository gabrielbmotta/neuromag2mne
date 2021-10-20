#ifndef NEUROMAG2MNE_STRINGCALLBACKPAIR_H
#define NEUROMAG2MNE_STRINGCALLBACKPAIR_H

#include <string>

struct StringCallbackPair
{
    StringCallbackPair(const std::string& s, void(*fcn)(void*), void* call);

    bool operator==(const StringCallbackPair& other) const;
    std::string trigger_string;
    void(*callback)(void*);
    void* objPtr;
};

#endif //NEUROMAG2MNE_STRINGCALLBACKPAIR_H
