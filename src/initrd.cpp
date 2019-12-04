#include <initrd.hpp>
#include <memio.h>
#include <stdio.h>

void Initrd::initalize(uint32_t baseAddr, uint32_t size)
{
    this->baseAddress = baseAddr;
    this->totalSizeInBlocks = size / 4096;

    printf("Initrd Initalized, Base Address: 0x%h, Size: 0x%h \n", this->baseAddress, this->totalSizeInBlocks);
}

int Initrd::read_block(void * buffer, uint32_t addr)
{
    uint8_t * cpyAddr = (uint8_t*)(addr + this->baseAddress);
    memcpy(buffer, cpyAddr,1024);
    return 0;
}

int Initrd::write_block(void * buffer, uint32_t addr)
{
    return -1;
}

uint32_t Initrd::get_blk_count()
{
    return this->totalSizeInBlocks;
}
