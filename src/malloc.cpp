#include <stddef.h>
#include <stdint.h>
#include <pmm.hpp>
#include <liballoc.h>


extern "C" int liballoc_lock()
{
	return 0;
}

extern "C" int liballoc_unlock()
{
	return 0;
}

extern "C" void* liballoc_alloc( int pages )
{
	void * allocatedPages = pmm.AllocPage(pages);
	return allocatedPages;
}

extern "C" int liballoc_free( void* ptr, int pages )
{
	pmm.FreePage(ptr, pages);
	return 0;
}
 
void *operator new(size_t size)
{
    return malloc(size);
}
 
void *operator new[](size_t size)
{
    return malloc(size);
}
 
void operator delete(void *p)
{
    free(p);
}
 
void operator delete(void *p, unsigned int s)
{
	if(s != 0)
	{
		free(p);
	}
}

void operator delete[](void *p)
{
    free(p);
}

 void operator delete [](void *p, unsigned int s)
 {
	 if(s != 0)
	 {
		 free(p);
	 }
 }
