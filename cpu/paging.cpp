#include "paging.h"
#include "../libc/mem.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/macros.h"

//kernel's page directory
page_directory_t *kernel_directory = 0;
// current page dir
page_directory_t *current_directory = 0;

// frame allocation and shit
// cant use std::bitset hmmm
uint32_t *frames;
uint32_t nframes;

extern uint32_t free_mem_addr; // defined in mem.cpp

#define INDEX_FROM_BIT(a) (a/32)
#define OFFSET_FROM_BIT(a) (a%32)

//set bit/frame
static void set_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}
//clear it
static void clear_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
} 

//test if set
static uint32_t test_frame(uint32_t frame_addr){
    uint32_t frame = frame_addr/0x1000;
    uint32_t idx = INDEX_FROM_BIT(frame);
    uint32_t off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

//find first free frame
static int32_t first_frame(){
    uint32_t i,j;
    for(i = 0; i < INDEX_FROM_BIT(nframes);i++){
        if(frames[i] == 0xFFFFFFFF) continue;
        for(j =0; j < 32; j++){
            uint32_t toTest = 0x1<<j;
            if(!(frames[i]&toTest)) return i*32+j;
        }
    }
}

// actual allocation
void alloc_frame(page_t *page, int is_kernel, int is_writable){
    if(page->frame != 0) return;

    uint32_t idx = first_frame();
    if(idx == (uint32_t)-1){
        PANIC("No free frames!");
    }
    set_frame(idx* 0x1000);
    page->present = 1; // mark as present
    page->rw = (is_writable)? 1 : 0; // r/w 
    page->user = (is_kernel)? 0 : 1; // user/supervisor
    page->frame = idx; // index in the table
}

//and deallocation
void free_frame(page_t *page){
    uint32_t frame;
    //no frame allocated for this page
    if(!(frame= page->frame)) return;     
    //clear
    clear_frame(frame);
    page->frame = 0x0;
}


//set up and enable paging
void init_paging(){
    //size of physical memory, 16MB for now
    uint32_t mem_end_page = 0x1000000;

    nframes = mem_end_page/0x1000;
    frames = (uint32_t*) kmalloc(INDEX_FROM_BIT(nframes));
    memory_set(frames, 0, INDEX_FROM_BIT(nframes));
    
    //create a page directory
    kernel_directory = (page_directory_t*)
    kmalloc_a(sizeof(page_directory_t));
    // the bug was this line. i have no idea why, but uncommenting it,
    // breaks the whole systems. took me about 4 days to debug...
   // memory_set(kernel_directory,0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    int i = 0;
    while(i < 0x1000000){
        alloc_frame(get_page(i,1,kernel_directory),1,1);
        i += 0x1000;
    }

    // register our page to page fault handler
    register_interrupt_handler(14, page_fault);
   
    //enable paging
    switch_page_directory(kernel_directory);
}

// loads specified page directory into cr3
void switch_page_directory(page_directory_t *dir){
    current_directory = dir;
    asm volatile("mov %0, %%cr3" :: "r"(&dir->tablesPhysical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // enable paging
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
    //PANIC("test 1\n");
}
// retries pointer to the page required
// if make==1, create the table if neccessary
page_t *get_page(uint32_t address, int make, page_directory_t *dir){
    //turn address into index
    address /= 0x1000;
    //find the page table containing this address
    uint32_t table_idx = address / 1024;
    if(dir->tables[table_idx]){
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(make){
        uint32_t tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t),&tmp);
        memory_set(dir->tables[table_idx], 0,0x1000);
        dir->tablesPhysical[table_idx] = tmp | 0x7; //present, rw, us
        return &dir->tables[table_idx]->pages[address%1024];
    }
    return 0;
}

// page fault handler
void page_fault(registers_t *regs){
    uint32_t faulting_address;
    asm ("mov %%cr2, %0" : "=r" (faulting_address));

    // get detailed error code
    int present = !(regs->err_code & 0x1); // page not present
    int rw = regs->err_code & 0x02; // write operation
    int us = regs->err_code & 0x4; // was proccesor in user mode?
    int reserved = regs->err_code & 0x8; // overwritten cpu-reversed bits of page entry?
    int id = regs->err_code & 0x10; // caused by instruction fetch?

    kprint("Page fautl! ( ");
    if(present) kprint("present ");
    if(rw) kprint("read-only ");
    if(us) kprint("user-mode ");
    if(reserved) kprint("reserved");
    kprint(") at 0x");
    kprint(" yeah i didnt bother converting to hex so gl\n");
    PANIC("Page fault");
}

