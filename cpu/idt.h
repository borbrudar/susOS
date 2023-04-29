#pragma once
#include "types.h"

//segment selectors
#define KERNEL_CS 0x08

// define interrupt gate datatype
typedef struct{
	u16 low_offset; // lower 16 bits of handler function address
	u16 sel; // kernel segment selector
	u8 always0;
	/* bit 7 - interrupt is present, 6-5 privilege lvl,
	   4- set to 0 for interrupt gates, 3-0: 1110 (32-bit
	   interrupt gate) */
	u8 flags;
	u16 high_offset; // the other half
} __attribute__((packed)) idt_gate_t;


// also the pointer to interrupt handlers
typedef struct{
	u16 limit;
	u32 base;
} __attribute__((packed)) idt_register_t;



//functions
void set_idt_gate(int n, u32 handler);
void set_idt();
