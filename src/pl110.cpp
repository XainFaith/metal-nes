#include <pl110.hpp>
#include <stdio.h>
#include <memio.h>


pl110 lcd;

int pl110::Initalize(uint32_t baseAddress)
{
    this->registers = (Registers*)baseAddress;
    /* 640x480 pixels */
	this->registers->tim0 = 0x3f1f3f9c;
	this->registers->tim1 = 0x080b61df;

    this->displayFormat.ResWidth = 640;
    this->displayFormat.ResHeight = 480;

    this->frameBuffer = new uint16_t[(this->displayFormat.ResWidth * this->displayFormat.ResHeight)];

    //this->frameBuffer = (uint16_t*)memset(this->frameBuffer, 0,640 * 480 * 2);
    int count = 0; 
    while(count < 640 * 480) //
    {
       this->frameBuffer[count] = 0;
       count++;
    }

    this->registers->upbase = (uint32_t)this->frameBuffer;

    //Set 16 bit color
    this->registers->control = 0x1829;

    
    this->displayFormat.colorMode = ColorMode::Color16;

    return 0;
}

void * pl110::getRawFrameBuffer()
{
    return (void*)this->frameBuffer;
}

DisplayFormat pl110::getDisplayFormat()
{
    return this->displayFormat;
}

