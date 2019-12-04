#ifndef GFX_DRIVER
#define GFX_DRIVER

#include <stdint.h>

enum ColorMode
{
    Pallete,
    Color16,
    Color32
};

struct DisplayFormat
{
    uint32_t ResWidth;
    uint32_t ResHeight;
    ColorMode colorMode;
};

class GfxDriver
{
    public:
    virtual int Initalize(uint32_t baseAddr)=0;
    virtual void * getRawFrameBuffer()=0;
    virtual DisplayFormat getDisplayFormat()=0;
};

#endif
