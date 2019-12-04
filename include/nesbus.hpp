#ifndef NES_BUS_HPP
#define NES_BUS_HPP

#include <stdint.h>

class NesBus
{
    public:
    NesBus();
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool readOnly = false);
    
    //Pointer to Nes Ram
    uint8_t * ram;

    //Util function for debugging
    uint8_t peek_mem(uint16_t addr);
};


#endif
