#include <iostream>
#include "tagparser.hpp"

TagParser::TagParser()
{

}

void TagParser::processTag(const fiff::Tag& tag)
{
    switch (tag.kind){
        case FIFF_NCHAN:
            break;

        case FIFF_SFREQ:
            break;

        case FIFF_BLOCK_START:
            break;
        default:
            std::cout << "tagparser.processTag: Unknown Tag Kind\n";
            break;
    }
}


