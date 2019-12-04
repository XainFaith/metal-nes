#ifndef PMM_H
#define PMM_H

#ifndef AVALIABLE_MEMORY
#define AVALIABLE_MEMORY 131072
#endif


#include <stdint.h>

class PhysicalMemoryManager
{
    public:
    
    int32_t Initalize(uint32_t baseOfFreeMem);
    void * AllocPage(uint32_t numOfPages);
    void FreePage(void * addr, uint32_t numOfPages);
    
    private:

    struct MemChunk
    {
        uint32_t chunkPageCount;
        MemChunk * prev;
        MemChunk * next;
    };

    void MergeChunks(MemChunk* prior, MemChunk* freed, MemChunk* post);


    uint32_t MemoryUsed;
    uint32_t TotalMemory;

    MemChunk * rootChunk;
};

extern PhysicalMemoryManager pmm;

#endif
