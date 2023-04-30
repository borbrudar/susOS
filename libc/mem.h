#pragma once
#include "../cpu/types.h"

void memory_copy(char *source, char* dest, int no_bytes);
void memory_set(u8 *dest, u8 val, u32 len);