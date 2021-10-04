#ifndef TYPES
#define TYPES
struct Tag
{
    int kind;
    int type;
    int size;
    int next;
    char* data;
};

struct MeasurementInfo
{
    float   sampleFrequency;
    int     numChannels;
};

#endif // TYPES

