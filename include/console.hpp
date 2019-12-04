#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <stdint.h>
#include <stddef.h>
#include <gfxdriver.hpp>

extern "C" void* memcpy(void* __restrict, const void* __restrict, size_t);
extern "C" void* memset(void*, int, size_t);

enum ConsoleColor
{
    White,
    Black,
    Green,
    Blue,
    Red,
    Yellow
};


class Console
{
    public:
    int Initalize(GfxDriver *gfxDriver);
    void Write(char c);

    int SetColor(ConsoleColor bg, ConsoleColor fg);
    void ClearScreen();

    private:

    void Scroll();

    void * frameBuffer;
    uint32_t getPixelColor(ConsoleColor color);
    void SetPixel(uint32_t x, uint32_t y,uint32_t pixelData);
    DisplayFormat displayFormat;

    uint32_t lineWdith;
    uint32_t x;
    uint32_t bgColor;
    uint32_t fgColor;

};

extern Console console;

#endif
