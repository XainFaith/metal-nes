#include <nesbus.hpp>

NesBus::NesBus()
{
    this->ram = new uint8_t[64 * 1024];
}

void NesBus::write(uint16_t addr, uint8_t data)
{
    if(addr >= 0x0000 && addr <= 0xFFFF)
    {
        this->ram[addr] = data;
    }
}

uint8_t NesBus::read(uint16_t addr, bool readOnly)
{
    if(addr >= 0x0000 && addr <= 0xFFFF)
    {
        return this->ram[addr];
    }

    return 0x0;
}

//Util function for debugging
uint8_t NesBus::peek_mem(uint16_t addr)
{
    if(addr >= 0x0000 && addr <= 0xFFFF)
    {
        return this->ram[addr];
    }
}
