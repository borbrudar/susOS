#include "mem.h"

void memory_copy(char *source, char *dest, int no_bytes){
	for(int i = 0;i < no_bytes;i++){
		*(dest+i) = *(source+i);
	}
}

void memory_set(uint8_t *dest,uint8_t val, uint32_t len){
	uint8_t* temp=(uint8_t*) dest;
	for(; len != 0; len--) *temp++ = val;
}


//libc functions
void *memmove(void *dstptr,const void*srcptr, size_t size){
    uint8_t *dst = (uint8_t*)dstptr;
    const uint8_t* src = (const uint8_t*) srcptr;
    if(dst < src){
        for(size_t i =0;i < size;i++) 
            dst[i] = src[i];
    }else{
        for(size_t i =size;i != 0;i--)
            dst[i-1] = src[i-1];
    }
    return dstptr;
}

int memcmp(const void*aptr, const void*bptr, size_t size){
    const uint8_t *a = (const uint8_t*) aptr;
    const uint8_t *b = (const uint8_t*) bptr;
    for(size_t i = 0;i < size;i++){
        if(a[i] < b[i]) return -1;
        else if(b[i] < a[i]) return 1;
    }
    return 0;
}

void *memset(void *bufptr, int value ,size_t size){
    uint8_t* buf = (uint8_t*) bufptr;
    for(size_t i = 0;i < size;i++)
        buf[i] = (uint8_t)value;
    return bufptr;
}

//should be calculated at link time, hardcore for now
uint32_t free_mem_addr = 0x10000;
//ptr to free memory that keeps growing
uint32_t kmalloc_int(size_t size, int align, uint32_t *phys_addr){
    // pages are align to 4k or 0x1000
   if(align == 1 && (free_mem_addr & 0x00000FFF)){
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    // save the physical address
    if(phys_addr) *phys_addr = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size; // inc the pointer
    return ret;
}

// page aligned
uint32_t kmalloc_a(size_t size){
    return kmalloc_int(size, 1, 0);
} 
// returns a physical address
uint32_t kmalloc_p(size_t size,uint32_t *phys){
    return kmalloc_int(size, 0, phys);
} 
// page aligned and physical address
uint32_t kmalloc_ap(size_t size, uint32_t *phys){
    return kmalloc_int(size,1,phys);
}
//vanilla
uint32_t kmalloc(size_t size){
    return kmalloc_int(size,0,0);
}