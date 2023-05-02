#pragma once
#include "../cpu/types.h"
#include <stddef.h>


void memory_copy(char *source, char* dest, int no_bytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

void *memmove(void *dstptr,const void*srcptr, size_t size);
int memcmp(const void*aptr, const void*bptr, size_t size);
void *memset(void *bufptr, int value ,size_t size);

uint32_t kmalloc_int(size_t size, int align, uint32_t *phys_addr);
uint32_t kmalloc_a(size_t size); // page aligned
uint32_t kmalloc_p(size_t size,uint32_t *phys); // returns a physical address
uint32_t kmalloc_ap(size_t size, uint32_t *phys); // page aligned and physical address
uint32_t kmalloc(size_t size); //vanilla