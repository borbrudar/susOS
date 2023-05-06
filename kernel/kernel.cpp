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
#include "shell.h"

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
