#pragma once

#include "../libc/macros.h"
#include "../libc/mem.h"
#include "isr.h"


typedef struct page{
    uint32_t present  : 1;  // page present in memory
    uint32_t rw       : 1;  // read/write (0 read, 1 rw)
    uint32_t user     : 1;  // user or supervisor mode
    uint32_t accessed : 1;  // accessed since last refreshed?
    uint32_t dirty    : 1;  // written to since last refresh?
    uint32_t unused   : 7;  // free for use by our OS
    uint32_t frame    : 20; // frame address (shifted right 12 bits)
} page_t;

typedef struct page_table{
    page_t pages[1024]  __attribute__((aligned(4096)));
} page_table_t;

typedef struct page_directory{
    // ptrs to page tables
    page_table_t *tables[1024]  __attribute__((aligned(4096)));;
    // ptrs to page tables, but their physical address
    // for loading into CR3 register
    uint32_t tablesPhysical[1024]  __attribute__((aligned(4096)));;
    
    //physical address of tablesPhysical
    //important for kernel heap and virtual memory
    uint32_t physicalAddr;
} page_directory_t;


//set up and enable paging
void init_paging();

// loads specified page directory into cr3
void switch_page_directory(page_directory_t *nowo);

// retries pointer to the page required
// if make==1, create the table if neccessary
page_t *get_page(uint32_t address, int make, page_directory_t *dir);

// page fault handler
void page_fault(registers_t *regs);

void alloc_frame(page_t *page, int is_kernel, int is_writable);
void free_frame(page_t *page);


