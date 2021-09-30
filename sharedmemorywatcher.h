#pragma once

#include "types.h"

class SharedMemoryWatcher
{
public:
    SharedMemoryWatcher();

    void watch();

private:

    void connectToSharedMemory();

    void processTag(const Tag& tag);

    Tag getTagFromShMem();

    Measurement* currentMeasurement;
};