#include "fiff.h"
#include <iostream>

struct Tag
{
    int kind;
    int type;
    int size;
    int next;
    char* data;
};


struct Measurement
{
    float   sampleFrequency;
    int     numChannels;
};

class ShMemWatcher
{
public:
    ShMemWatcher();



private:

    void connectToSharedMemory()
    {

    }

    void processTag(const Tag& tag)
    {
        switch (tag.kind)
    }

    Tag getTagFromShMem()
    {

    }

    Mesurement* currentMeasurement;
};



int main (int argc, char* argv[])
{
    SharedMemWatcher watcher;
    connectToSharedMemory();

    bool keepReading = true;

    while(keepReading){
        auto tag = getTagFromShMem();
        processTag(tag);
    }
    return 0;
}