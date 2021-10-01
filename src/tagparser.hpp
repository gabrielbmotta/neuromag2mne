#ifndef TAGPARSER
#define TAGPARSER

#include "fiff.hpp"
#include "types.hpp"

class TagParser
{
public:
    TagParser();
private:
    void processTag(const Tag& tag);
};


#endif