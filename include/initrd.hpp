#ifndef INITRD_HPP
#define INITRD_HPP

#include <stdint.h>
#include <blockdevice.hpp>

class Initrd : public BlockDevice
{
    public:
    void initalize(uint32_t baseAddr, uint32_t size);
    int read_block(void * buffer, uint32_t addr);
    int write_block(void * buffer, uint32_t addr);
    uint32_t get_blk_count();

    private:
     uint32_t baseAddress;
     uint32_t totalSizeInBlocks;
};

#endif
