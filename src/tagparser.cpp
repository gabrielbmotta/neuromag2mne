#include "tagparser.hpp"

void TagParser::processTag(const Tag& tag)
{
    switch (tag.kind){
        case FIFF_NCHAN:
            break;

        case FIFF_SFREQ:
            break;

        case FIFF_BLOCK_START:
            break;

    }
}

