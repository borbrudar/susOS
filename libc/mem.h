#pragma once
#include "../cpu/types.h"

void memory_copy(char *source, char* dest, int no_bytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

uint32_t kmalloc(uint32_t size, int align, uint32_t *phys_addr);