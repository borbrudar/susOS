#pragma once
#include "types.h"

// ISR reserved for cpu exception
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

// define irq or interrupt requests
#define irq0 32
#define irq1 33
#define irq2 34
#define irq3 35
#define irq4 36
#define irq5 37
#define irq6 38
#define irq7 39
#define irq8 40
#define irq9 41
#define irq10 42
#define irq11 43
#define irq12 44
#define irq13 45
#define irq14 46
#define irq15 47



//registers struct for some reason idfk
typedef struct{
	u32 ds; // data segment
	u32 edi, esi, ebp, esp, edx, ecx, eax; // used by pusha
	u32 int_no, err_code; // self explanatory
	u32 eip, cs, eflags, useresp, ss; // pushed by cpu automatically
} registers_t;

extern "C" void isr_install();
extern "C" void isr_handler(registers_t r);

typedef void (*isr_t)(registers_t);
extern "C" void register_interrupt_handler(u8 n,isr_t handler);
