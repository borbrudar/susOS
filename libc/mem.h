#pragma once
#include "types.h"
#include <stddef.h>

void* memcpy(void* dstptr, const void* srcptr, size_t size);
void *memmove(void *dstptr,const void*srcptr, size_t size);
int memcmp(const void*aptr, const void*bptr, size_t size);
void *memset(void *bufptr, int value ,size_t size);
