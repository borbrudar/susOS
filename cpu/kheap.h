#pragma once
#include "types.h"

typedef struct{
    uint32_t magic; // error checking and identification
    uint8_t is_hole; //1-hole ,0-block
    uint32_t size; // size including header and footer
} header_t;

typedef struct{
    uint32_t magic; // same as header
    header_t *header; //ptr to header
} footer_t;