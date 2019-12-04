#include <pmm.hpp>

#include <uart.hpp>
#include <gfxdriver.hpp>
#include <console.hpp>

#include <pl110.hpp>

#if QEMU
    #include <initrd.hpp>
#else
    #include <pl181.hpp>
#endif

#include <nesbus.hpp>
#include <nes6502.hpp>

#include <stdio.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTER 0x18
#define SERIAL_BUFFER_FULL (1 << 5)
 
 extern uint32_t * __kernel_end;


void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}

extern "C" int putchar (char c)
{
   uart.WriteChar(c);
   console.Write(c);
   return 1;
}

extern "C" int main (void)
{
    uint32_t kernelEndAddr = (uint32_t)&__kernel_end;
    pmm.Initalize(kernelEndAddr);
    
    uart.Initalize(0x16000000);

    lcd.Initalize(0xC0000000);

    console.Initalize((GfxDriver*)&lcd);
    console.SetColor(ConsoleColor::Black, ConsoleColor::Green);

    NesBus * nes_bus = new NesBus();
    Nes6502 * nesCpu = new Nes6502();

    nesCpu->connect_bus(nes_bus);
    nesCpu->reset();
    
while(1){}

    return 0;
}
