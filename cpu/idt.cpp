#include "idt.h"
#include "../kernel/util.h"

//all entries must be defined
#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


void set_idt_gate(int n,u32 handler){
	idt[n].low_offset = low_16(handler);
	idt[n].sel = KERNEL_CS;
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler);
}

void set_idt(){
	idt_reg.base = (u32) &idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) -1;
	// load idt_reg not idt
	__asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
}
