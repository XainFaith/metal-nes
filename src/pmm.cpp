#include "pmm.hpp"

PhysicalMemoryManager pmm;

//Initalizes and builds the tree for tracking phsyical memory as pages 4kb in size
int32_t PhysicalMemoryManager::Initalize(uint32_t baseOfFreeMem)
{

    //Set used memory to be that of the kernels size ((kernelSize / 4096) + 1) * 4096
    //The above bit of math is used to ensure the memory used is a 4kb page boundary and if the used size passed in was
    //Not 4kb aligned we add a full page frame just to be sure 
    this->MemoryUsed = ((baseOfFreeMem / 4096) + 1) * 4096;
    this->MemoryUsed = (baseOfFreeMem * 1024);
    #if QEMU
    //We divide the avaliable memory by 2 because we use an initrd in memory as a file systems since the pl181 is currntly broken on qemu
    this->TotalMemory = AVALIABLE_MEMORY / 2 * 1024;
    #else
    this->TotalMemory = AVALIABLE_MEMORY * 1024;
    #endif

    MemChunk * memChunkPtr = (MemChunk*)this->MemoryUsed;
    this->rootChunk = memChunkPtr;

    memChunkPtr->chunkPageCount = (this->TotalMemory - this->MemoryUsed) / 4096;
    memChunkPtr->prev = nullptr;
    memChunkPtr->next = nullptr;    

    return 0;
}

void * PhysicalMemoryManager::AllocPage(uint32_t numOfPages)
{
    if(this->rootChunk != nullptr)
    {
        //Setup a pointer for iterating over the list
        MemChunk * memChunkPtr = this->rootChunk;

        //Loop while the pointer for iteration is not null
        while(memChunkPtr != nullptr)
        {
            //Is the chunk larger or equal too the number of pages requested
           if(memChunkPtr->chunkPageCount >= numOfPages)
           {
                //is the chunk exactly the correct size
                if(memChunkPtr->chunkPageCount == numOfPages)
                {
                    //If there was a chunk prior to the allocated chunk
                    if(memChunkPtr->prev != nullptr)
                    {
                        //Is there a chunk after the allocated chunk
                        if(memChunkPtr->next != nullptr)
                        {
                            //Set the prior chunk to point to the next one beyond the allocated chunk
                            memChunkPtr->prev->next = memChunkPtr->next;
                        }
                        else //If there is no chunk beyond the allocated chunk set the prior chunks next link to nullptr
                        {
                            memChunkPtr->prev->next = nullptr;
                        }
                    }
                    else //If there is no prior chunk this must be the root node
                    {
                        //Is there a chunk after the allocated chunk
                        if(memChunkPtr->next != nullptr)
                        {
                            //Set the root chunk to be the chunk beyond the allocated chunnk
                            this->rootChunk = memChunkPtr->next;
                        }
                        else
                        {
                            //We are not out of memory
                            this->rootChunk = nullptr;
                        }
                        
                    }
                    
                    this->MemoryUsed += numOfPages * 4096;
                    //Return the allocated chunk
                    return (void*)memChunkPtr;
                }
                
                //If the chunk is larger
                if(memChunkPtr->chunkPageCount > numOfPages)
                {
                    //Calculate the address of the break
                    uint32_t baseAddr = (uint32_t)memChunkPtr;
                    uint32_t breakAddr = baseAddr + (numOfPages * 4096);

                    //Create the new chunk data
                    MemChunk * newChunkPtr = (MemChunk*)(breakAddr);
                    newChunkPtr->next = memChunkPtr->next;
                    newChunkPtr->prev = memChunkPtr->prev;
                    newChunkPtr->chunkPageCount = memChunkPtr->chunkPageCount - numOfPages;
                    
                    //If there is a chunk prior to the allocated one set its next pointer to the new chunk
                    if(memChunkPtr->prev != nullptr)
                    {
                        memChunkPtr->prev->next = newChunkPtr;
                    }
                    else //If there is no chunk prior to the allocated on set the new chunk as the root chunk
                    {
                        this->rootChunk = newChunkPtr;
                    }
                    
                    this->MemoryUsed += numOfPages * 4096;
                    //Return the allocated chunk
                    return (void*)memChunkPtr;
                }

                //Iterate to the next chunk to see if the next one has space for the allocation
                memChunkPtr = memChunkPtr->prev;
           }

        }
    }
    
    return nullptr;
}

void PhysicalMemoryManager::FreePage(void * addr, uint32_t numOfPages)
{
    //Sainity check on the values passed in
    if(addr != nullptr && numOfPages != 0)
    {
        //Check to see if there is a root chunk
        if(this->rootChunk != nullptr)
        {
            uint32_t freeAddr = (uint32_t)addr;

            //Iterate over the list of free chunks 
            MemChunk * memChunkPtr = this->rootChunk;
            while(memChunkPtr != nullptr)
            {
                //If the chunk being returned has an address less the the chunk we are checking its place belongs before that chunk
                uint32_t chunkAddr = (uint32_t)memChunkPtr;
                if(freeAddr < chunkAddr)
                {
                    MemChunk * freedPtr = (MemChunk*)addr;
                    freedPtr->chunkPageCount = numOfPages;
                    freedPtr->next = memChunkPtr;
                    freedPtr->prev = memChunkPtr->prev;

                    this->MergeChunks(memChunkPtr->prev, freedPtr, memChunkPtr);
                    break;
                }
            }
        }
        else
        {
            //We ran out of memory and this is the first free call since then, So just set the freed pages chunk as the root chunk
            this->rootChunk = (MemChunk*)addr;
            this->rootChunk->chunkPageCount = numOfPages;
            this->rootChunk->prev = nullptr;
            this->rootChunk->next = nullptr;
        }

        //adjust for the freed memory
        this->MemoryUsed -= numOfPages * 4096;        
    }
}

void PhysicalMemoryManager::MergeChunks(MemChunk* prior, MemChunk* freed, MemChunk* post)
{
    //If there is a chunk prior
    if(prior != nullptr)
    {
        //check to see if its boundarys line up with the freed chunk if they do then they need to be merged
        if((((uint32_t)prior) + (prior->chunkPageCount * 4096)) == (uint32_t)freed)
        {
            prior->chunkPageCount += freed->chunkPageCount;
            prior->next = post;

            //Set the freed chunk to be the prior chunk since they have merged
            freed = prior;
        }
    }

    //If there is a chunk post the freed chunk
    if(post != nullptr)
    {
        //check to see if its boundarys line up with the freed chunk if they do then they need to be merged
        if((((uint32_t)freed) + freed->chunkPageCount * 4096) == (uint32_t)post)
        {
            freed->chunkPageCount += post->chunkPageCount;
            freed->next = post->next;
        }
    }
}
