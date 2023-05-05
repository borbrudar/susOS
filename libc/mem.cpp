#include "mem.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void memory_copy(char *source, char *dest, int no_bytes){
	for(int i = 0;i < no_bytes;i++){
		*(dest+i) = *(source+i);
	}
}
/*
legacy

void memory_set(void *dest,uint8_t val, uint32_t len){
	uint8_t* temp=(uint8_t*) dest;
	for(; len != 0; len--) *temp++ = val;
}
*/

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

// i need to use the shitty one for some reason
void *memset(void *bufptr, int value ,size_t size){
    uint8_t* buf = (uint8_t*) bufptr;
    for(size_t i = 0;i < size;i++)
        buf[i] = (uint8_t)value;
    return bufptr;
}