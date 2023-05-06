#include "shell.h"
#include "bits.h"
#include "screen.h"
#include "kheap.h"

void user_input(char *input){
	if(strcmp(input, (const char*)"END") == 0){
		kprint("Stopping the CPU. Nyan-out!\n");
		asm volatile("hlt");
	} else if(strcmp(input, (const char*)"PAGE") == 0){
		// test kmalloc
		uint32_t phys_addr;
		uint32_t page = kmalloc_int(1000,1,&phys_addr);
		char page_str[16] = "";
		hex_to_ascii(page,page_str);
		char phys_str[16] = "";
		hex_to_ascii(phys_addr,phys_str);
		
		kprint("Page: ");
		kprint(page_str);
		kprint(", physical address: ");
		kprint(phys_str);
		kprint("\n");
	}	
	kprint("You typed: ");
	kprint(input);
	kprint("\n>");
}
