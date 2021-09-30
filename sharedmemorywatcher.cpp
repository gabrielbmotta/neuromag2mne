#include "sharedmemorywatcher.hpp"
#include "fiff.hpp"

SharedMemoryWatcher::SharedMemoryWatcher()
{

}

void SharedMemoryWatcher::watch()
{
    m_isWatching = true;

    while (m_isWatching)
    {
        auto tag = getTagFromShMem();
        processTag(tag);
    }
}

void SharedMemoryWatcher::connectToSharedMemory()
{

}

void SharedMemoryWatcher::processTag(const Tag& tag)
{
    switch (tag.kind){
        case FIFF_NCHAN:
            m_currentMeasurement.numChannels = *((float*)(tag.data));
            break;

        case FIFF_SFREQ:
            m_currentMeasurement.sampleFrequency = *((float*)(tag.data));
            break;

        case FIFF_BLOCK_START:
            break;

    }
}

Tag SharedMemoryWatcher::getTagFromShMem()
{
    Tag tag;
    return tag;
}

