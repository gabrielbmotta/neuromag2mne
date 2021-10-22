#ifndef NEUROMAG2MNE_TYPES_HPP
#define NEUROMAG2MNE_TYPES_HPP

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

#endif // NEUROMAG2MNE_TYPES_HPP

