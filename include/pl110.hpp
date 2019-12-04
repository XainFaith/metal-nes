#ifndef PL110_HPP
#define PL110_HPP

#include <gfxdriver.hpp>
#include <stdint.h>


class pl110  : public GfxDriver
{
    public:
    int Initalize(uint32_t baseAddr);
    void * getRawFrameBuffer();
    DisplayFormat getDisplayFormat();

    private:
    struct Registers
    {
        uint32_t volatile tim0;		//0
        uint32_t volatile tim1;		//4
        uint32_t volatile tim2;		//8
        uint32_t volatile d;		//c
        uint32_t volatile upbase;	//10
        uint32_t volatile f;		//14
        uint32_t volatile g;		//18
        uint32_t volatile control;	//1c
    };

    Registers * registers;
    volatile uint16_t  * frameBuffer;

    DisplayFormat displayFormat;
};

extern pl110 lcd;

#endif
