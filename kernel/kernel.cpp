#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include <stdint.h>

extern "C" void kernel_main(){
	isr_install();
	irq_install();
	//kprint(">");
}

void user_input(char *input){
	if(strcmp(input, "END") == 0){
		kprint("Stopping the CPU. Nyan-out!\n");
		asm volatile("hlt");
	} else if(strcmp(input, "PAGE") == 0){
		// test kmalloc
		uint32_t phys_addr;
		uint32_t page = kmalloc(1000,1,&phys_addr);
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
