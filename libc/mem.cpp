#include "mem.h"

void memory_copy(char *source, char *dest, int no_bytes){
	for(int i = 0;i < no_bytes;i++){
		*(dest+i) = *(source+i);
	}
}

void memory_set(u8 *dest,u8 val, u32 len){
	u8* temp=(u8*) dest;
	for(; len != 0; len--) *temp++ = val;
}

//should be calculated at link time, hardcore for now
u32 free_mem_addr = 0x10000;
//ptr to free memory that keeps growing
u32 kmalloc(u32 size, int align, u32 *phys_addr){
    // pages are align to 4k or 0x1000
   if(align == 1 && (free_mem_addr & 0xFFFFF000)){
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    // save the physical address
    if(phys_addr) *phys_addr = free_mem_addr;

    u32 ret = free_mem_addr;
    free_mem_addr += size; // inc the pointer
    return ret;
}