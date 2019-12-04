#include <uart.hpp>

UART uart;

void UART::Initalize(uint32_t baseAddr)
{
    //Initalize the registers to there addresses
    this->registers->Data = (char*) baseAddr;
    this->registers->DataFlags = (uint8_t*)baseAddr + 0x04;
    this->registers->Flags = (uint16_t*)baseAddr + 0x018;
    this->registers->Ilpr = (uint8_t*)baseAddr + 0x020;
    this->registers->BaudRate = (uint16_t*)baseAddr + 0x024;
    this->registers->BaudFrac = (uint8_t*)baseAddr + 0x028;
    this->registers->LineCrtl = (uint8_t*)baseAddr + 0x02C;
    this->registers->Ctrl = (uint16_t*)baseAddr + 0x030;
    this->registers->FifoLevelSel = (uint8_t*)baseAddr + 0x034;
    this->registers->IntMask = (uint16_t*)baseAddr + 0x038;
    this->registers->RawIntStatus = (uint16_t*)baseAddr + 0x03C;
    this->registers->MskIntStatus = (uint16_t*)baseAddr + 0x040;
    this->registers->IntClear = (uint16_t*)baseAddr + 0x044;
    this->registers->DmaCrtl = (uint8_t*)baseAddr + 0x048;

    // Disable UART
	*this->registers->Ctrl = 0x00000000;
    //Clear pending Interrupts
    *this->registers->IntClear = 0x7FF;

    //Set divider for baud rate, Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
    *this->registers->BaudRate = 1;
    *this->registers->BaudFrac = 40;

    // Enable FIFO & 8 bit data transmission (1 stop bit, no parity).
    *this->registers->LineCrtl = ((1 << 4) | (1 << 5) | (1 << 6));

    //Mask All Interrupts
    *this->registers->IntMask = ((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART, receive & transfer part of UART.
	*this->registers->Ctrl = ((1 << 0) | (1 << 8) | (1 << 9));
}

void UART::Write(const char * str)
{
    for (size_t i = 0; str[i] != '\0'; i ++)
    {
        this->WriteChar(str[i]);
    }
}

void UART::WriteChar(char c)
{
    //Wait for uart to be ready to transmit
    while(*this->registers->Flags & (1 << 5)) {}

    *this->registers->Data = c;
}
    
char UART::ReadChar()
{
    // Wait for UART to have received something.
    while ( *this->registers->Flags & (1 << 4) ) { }
    return *this->registers->Data;
}

char * UART::Read(size_t bytesToRead)
{
    char * data = new char[bytesToRead];
    uint32_t counter = 0;
    while(counter < bytesToRead)
    {
        data[counter] = this->ReadChar();
    }

    return data;
}

  