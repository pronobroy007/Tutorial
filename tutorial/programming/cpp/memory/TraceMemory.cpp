#include <cstddef>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <dlfcn.h>


struct MemoryInfo
{
    u_int32_t totalAllocated = 0;
    u_int32_t totalFreed = 0;
    
    void show()
    {
        std::cout << "Total Allocated : " << totalAllocated << " bytes" << std::endl;
        std::cout << "Total Deallocated : " << totalFreed << " bytes" << std::endl;
    }
};

MemoryInfo memoryInfo;
/************************************************************************
*  Whenever any function call new this function will triggerr.
*  So all dynamic allocation and deallocation happen here
*  and we can track how many mamory created and how many are freed
*************************************************************************/
typedef void * (*malloc_type_function)(size_t t);
void *malloc(size_t t)
{
    memoryInfo.totalAllocated += t;
    malloc_type_function sysmalloc = (malloc_type_function)dlsym(RTLD_NEXT, "malloc");
    void* result = sysmalloc(t);       //Calling actual malloc function.
    return result;
}
/*
    void* operator new(size_t s)
    {
        //Track how many bytes allocated
        memoryInfo.totalAllocated += s;
        return malloc(s);
    }
*/

//void operator delete(void* ptr)
void operator delete(void* ptr, size_t t) 
{
    //Track how many bytes are deallocated
    memoryInfo.totalFreed += t;
    free(ptr);
}
/**************************************************************************/



struct Vec { int x, y, z; };

int main()
{
    Vec* vec = new Vec;
    delete vec;

    memoryInfo.show();
    return 0;
}
