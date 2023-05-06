#include "screen.h"
#include "mem.h"
#include "string.h"
#include "isr.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"
#include <stdint.h>
#include "macros.h"
#include "paging.h"
#include "kheap.h"
#include "types.h"

extern "C" void kernel_main(){
	clear_screen();
	kprint(">");
	isr_install();
	irq_install();
	init_paging();
	
	//uint32_t a = kmalloc(8);
	kprint("Enabled paging\n");
	//PANIC("success");
	//uint32_t *ptr = (uint32_t*) 0xA0000000;
	//uint32_t *fault = *ptr;

	/*uint32_t b = kmalloc(8);
	uint32_t c = kmalloc(8);

	kprint(a);kprint("\n");
	kprint(b);kprint("\n");
	kprint(c);kprint("\n");

	kfree(c); kfree(b);
	uint32_t d = kmalloc(12);
	kprint(d);
	*/
}

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
