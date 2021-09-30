#pragma once

#include "types.hpp"
#include "shmem.hpp"

class SharedMemoryWatcher
{
public:
    SharedMemoryWatcher();
    void watch();

private:

    void connectToSharedMemory();

    void processTag(const Tag& tag);

    Tag getTagFromShMem();

    MeasurementInfo m_currentMeasurement;

    bool m_isWatching;
};