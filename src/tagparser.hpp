#ifndef NEUROMAG2MNE_TAGPARSER_HPP
#define NEUROMAG2MNE_TAGPARSER_HPP

#include "fiff/fiff.hpp"

class TagParser
{
public:
    TagParser();
private:
    void processTag(const fiff::Tag& tag);
};


#endif

