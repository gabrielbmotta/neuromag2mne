#ifndef TAGPARSER
#define TAGPARSER

#include "../fiff/fiff.hpp"
#include "types.hpp"

class TagParser
{
public:
    TagParser();
private:
    void processTag(const Tag& tag);
};


#endif

