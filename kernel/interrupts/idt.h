#pragma once
#include "types.h"

//segment selectors
#define KERNEL_CS 0x08

// define interrupt gate datatype
typedef struct{
	uint16_t low_offset; // lower 16 bits of handler function address
	uint16_t sel; // kernel segment selector
	uint8_t always0;
	/* bit 7 - interrupt is present, 6-5 privilege lvl,
	   4- set to 0 for interrupt gates, 3-0: 1110 (32-bit
	   interrupt gate) */
	uint8_t flags;
	uint16_t high_offset; // the other half
} __attribute__((packed)) idt_gate_t;


// also the pointer to interrupt handlers
typedef struct{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_register_t;

//functions
void set_idt_gate(int n, uint32_t handler);
void set_idt();
