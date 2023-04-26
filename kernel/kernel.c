#include "../drivers/screen.h"

int main(){
	clear_screen();
	kprint_at("X",6,1);
	kprint_at("Text that spans multiple lines apparently.", 10, 75);
	kprint_at("Line break here\n", 20, 0);
	kprint("And another\n one");
	kprint_at("What happens when we run out of space?", 24, 45);
}
