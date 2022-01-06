#ifndef NEUROMAG2MNE_TAGPARSER_HPP
#define NEUROMAG2MNE_TAGPARSER_HPP

#include "fiff/fifftag.hpp"

class TagParser
{
public:
    TagParser();
private:
    void processTag(const fiff::Tag& tag);
};


#endif

