#ifndef NEUROMAG2MNE_TAGPARSER_HPP
#define NEUROMAG2MNE_TAGPARSER_HPP

#include "fiff/fiff.hpp"
#include "neuromag/types.hpp"

class TagParser
{
public:
    TagParser();
private:
    void processTag(const Tag& tag);
};


#endif

