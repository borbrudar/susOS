#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main(){
	isr_install();
	irq_install();
	
}

void user_input(char *input){
	if(strcmp(input, "EEEENNNNDDDD") == 0){
		kprint("Stopping the CPU. Nyan-out!\n");
		asm volatile("hlt");
	}
	kprint("You typed: ");
	kprint(input);
	kprint("\n>");
}
