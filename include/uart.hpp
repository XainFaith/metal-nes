#ifndef UART_HPP
#define UART_HPP

#include <stdint.h>
#include <stddef.h>

class UART
{
    public:
    void Initalize(uint32_t baseAddr);
    void Write(const char * string);
    void WriteChar(char);
    char * Read(size_t bytesToRead);
    char ReadChar();

    private:
    struct UartRegisters
    {
        char * Data;
        uint8_t * DataFlags;
        uint8_t * RXStatus;
        uint16_t * Flags;
        uint8_t * Ilpr;
        uint16_t * BaudRate;
        uint8_t * BaudFrac;
        uint8_t * LineCrtl;
        uint16_t * Ctrl;
        uint8_t * FifoLevelSel;
        uint16_t * IntMask;
        uint16_t * RawIntStatus;
        uint16_t * MskIntStatus;
        uint16_t * IntClear;
        uint8_t * DmaCrtl;                
    };

    volatile UartRegisters * registers;

};

extern UART uart;

#endif
