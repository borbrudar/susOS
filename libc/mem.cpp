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
