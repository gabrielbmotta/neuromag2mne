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