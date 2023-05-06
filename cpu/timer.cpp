#include "timer.h"
#include "screen.h"
#include "string.h"
#include "ports.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs){
	tick++;
/*	kprint("Tick: ");
	char tick_ascii[256];
	int_to_ascii(tick,tick_ascii);
	kprint(tick_ascii);
	kprint("\n");
	*/
}

void init_timer(uint32_t freq){
	//register handler 
	register_interrupt_handler(IRQ0, timer_callback);

	//get the PIT value, hardware clock is 1193180 Hz
	uint32_t divisor = 1193180 / freq;
	uint8_t low = (uint8_t) (divisor & 0xFF);
	uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
	//send the command
	port_byte_out(0x43, 0x36);
	port_byte_out(0x40,low);
	port_byte_out(0x40,high);

	//port_byte_out(0x20,0x20);
}
