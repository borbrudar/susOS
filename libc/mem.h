#pragma once
#include "../cpu/types.h"
#include <stddef.h>

void memory_copy(char *source, char* dest, int no_bytes);
/*legacy
void memory_set(void *dest, uint8_t val, uint32_t len);
*/

void *memmove(void *dstptr,const void*srcptr, size_t size);
int memcmp(const void*aptr, const void*bptr, size_t size);
void *memset(void *bufptr, int value ,size_t size);
