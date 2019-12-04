#include <console.hpp>
#include <memio.h>
#include <font8x8.h>

#include <stdio.h>

Console console;

int Console::Initalize(GfxDriver * gfxDriver)
{
    this->displayFormat = gfxDriver->getDisplayFormat();
    //Setup the line width and height, dividing for the font width and height
    this->lineWdith = this->displayFormat.ResWidth / 8; 
    this->x = 0;
   
    this->frameBuffer = gfxDriver->getRawFrameBuffer();

    return 0;
}

void Console::Write(char c)
{
    if(c == '\n')
    {
        this->x = 0;
        this->Scroll();
        return;
    }

    //Get pixel coords for current glyph to be drawn
    uint32_t yPos = this->displayFormat.ResHeight - 8;
    //Font is 8 x 8
    int y =0;
    for(y = 0; y < 8; y++) //y is row
    {
        int row = font8x8_basic[(int)c][y]; //Get the data corresponding to the row
        for(int x = 0; x < 8; x++) //x is bit of row
        {
                bool bit = (row & (1 << (x - 1))) != 0; //Get the x th bit
                if(bit)
                {
                    this->SetPixel(this->x + x,yPos + y,this->fgColor);
                }
                else
                {
                    this->SetPixel(this->x + x,yPos + y,this->bgColor);
                }
        }
    }

    this->x += 8;
    if(this->x >= (this->displayFormat.ResWidth - 8))
    {
        this->x = 0;
        this->Scroll();
    }
}

void Console::Scroll()
{
    switch (this->displayFormat.colorMode)
    {
    case ColorMode::Color16:
    {
        uint16_t * fb16 = (uint16_t*)this->frameBuffer;
        memcpy(fb16, fb16 + (sizeof(uint16_t) * this->displayFormat.ResWidth * 8), sizeof(uint16_t) * this->displayFormat.ResWidth * this->displayFormat.ResHeight);
        memset(fb16 + (sizeof(uint16_t) * this->displayFormat.ResWidth * (this->displayFormat.ResHeight-8)),0,sizeof(uint16_t) * this->displayFormat.ResWidth * 8);
    }
        break;
    
    case ColorMode::Color32:
    {
        uint32_t * fb = (uint32_t*)this->frameBuffer;
        memcpy(fb, fb + (sizeof(uint32_t) * this->displayFormat.ResWidth * 8), sizeof(uint32_t) * this->displayFormat.ResWidth * this->displayFormat.ResHeight);
        memset(fb + (sizeof(uint32_t) * this->displayFormat.ResWidth * (this->displayFormat.ResHeight-8)),0,sizeof(uint32_t) * this->displayFormat.ResWidth * 8);
    }
        break;

    default:
        break;
    }
    
}

uint32_t Console::getPixelColor(ConsoleColor color)
{
    switch (this->displayFormat.colorMode)
    {
    case ColorMode::Color16:
        switch (color)
        {
        case ConsoleColor::Black :
            return 0;

        case ConsoleColor::Blue:
            return 0x003E;

        case ConsoleColor::Green:
            return 0x07C0;

        case ConsoleColor::Red :
            return 0xF800;

        case ConsoleColor::White:
            return 0xFFFE;

        case ConsoleColor::Yellow:
            return 0x07FE;
        }
        break;
    
    default:
        return 0;
    }

    return 0;
}

int Console::SetColor(ConsoleColor bg, ConsoleColor fg)
{
    this->bgColor = this->getPixelColor(bg);
    this->fgColor = this->getPixelColor(fg);
    return 0;
}

void Console::ClearScreen()
{
    switch (this->displayFormat.colorMode)
    {
    case ColorMode::Color16:
        memset(this->frameBuffer, 0, (this->displayFormat.ResHeight * this->displayFormat.ResWidth) * sizeof(uint16_t));
        return;

    case ColorMode::Color32:
        memset(this->frameBuffer, 0, (this->displayFormat.ResHeight * this->displayFormat.ResWidth) * sizeof(uint32_t));
        return;

    default:
        break;
    }
    
}

void Console::SetPixel(uint32_t x, uint32_t y,uint32_t pixelData)
{
    switch (this->displayFormat.colorMode)
    {
    case ColorMode::Color16 :
        ((uint16_t*)this->frameBuffer)[(y * this->displayFormat.ResWidth) + x] = (uint16_t)pixelData;
        break;
    
    case ColorMode::Color32:
        ((uint32_t*)this->frameBuffer)[(y * this->displayFormat.ResWidth) + x] = pixelData;
        break;

    default:
        break;
    }
}
