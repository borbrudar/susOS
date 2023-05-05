#pragma once
#include "types.h"
#include "../libc/ordered_array.h"
#include <stdint.h>

//#define KHEAP_START 0xC0000000
#define KHEAP_START 0x700000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x123489AB
#define HEAP_MIN_SIZE 0x70000

typedef struct{
    uint32_t magic; // error checking and identification
    uint8_t is_hole; //1-hole ,0-block
    uint32_t size; // size including header and footer
} header_t;

typedef struct{
    uint32_t magic; // same as header
    header_t *header; //ptr to header
} footer_t;

typedef struct{
    ordered_array_t index;
    uint32_t start_address;
    uint32_t end_address;
    uint32_t max_address;
    uint8_t supervisor;
    uint8_t readonly;
} heap_t;


heap_t *create_heap(uint32_t start,uint32_t end, uint32_t max,
uint8_t supervisor, uint8_t readonly);

void *alloc_heap(uint32_t *size, uint8_t page_align, heap_t *heap);

void free_heap(void *p, heap_t *heap);


uint32_t kmalloc_int(size_t size, int align, uint32_t *phys_addr);

void kfree(void *p);


uint32_t kmalloc_a(size_t size); // page aligned
uint32_t kmalloc_p(size_t size,uint32_t *phys); // returns a physical address
uint32_t kmalloc_ap(size_t size, uint32_t *phys); // page aligned and physical address
uint32_t kmalloc(size_t size); //vanilla