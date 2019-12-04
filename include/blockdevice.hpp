#ifndef BLOCK_DEVICE_HPP
#define BLOCK_DEVICE_HPP

class BlockDevice
{
    public:

    bool device_present;

    virtual int read_block(void * buffer, uint32_t addr) = 0;
    virtual int write_block(void * buffer, uint32_t addr) = 0;
    virtual uint32_t get_blk_count() = 0;
};

#endif
