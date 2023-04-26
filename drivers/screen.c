//printchar at col and row or cursor position
#include "../kernel/ports.h"
#include "screen.h"

int print_char(char ch, int row, int col, char attribute);
int get_screen_offset(int row, int col);
int get_cursor();
void set_cursor(int offset);
int get_offset_row(int offset);
int get_offset_col(int offset);


void clear_screen();

void kprint_at(char *message, int row, int col){
	int offset;
	if(col >=0 && row>=0) offset= get_screen_offset(row,col);
	else{
		offset = get_cursor();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	int i =0;
	while(message[i] != 0){
		offset = print_char(message[i++], row,col, WHITE_ON_BLACK);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void kprint(char *message){
	kprint_at(message,-1,-1);
}



// ----------------------------------------------------
//                        PRIVATE
// ----------------------------------------------------

int print_char(char ch, int row, int col, char attribute){
	unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
	// color and stuff
	if(!attribute) attribute = WHITE_ON_BLACK;

	//error
	if(col >= MAX_COLS || row >= MAX_ROWS){
		vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
		vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
		return get_screen_offset(row,col);
	}

	//calculate the offset
	int offset;
	if(col >= 0 && row >= 0) offset = get_screen_offset(row,col);
	else offset = get_cursor();

	// if newline go to newline
	if(ch == '\n'){
		row = get_offset_row(offset);
		offset = get_screen_offset(row+1,col);
	}else{
		vidmem[offset] = ch;
		vidmem[offset+1] = attribute;
		offset+=2;
	}

	set_cursor(offset);
	return offset;
}

//basic 2d matrix lol
int get_screen_offset(int row, int col){
	return 2*(row * MAX_COLS + col);
}
int get_offset_row(int offset){
	return offset/(2*MAX_COLS);
}
int get_offset_col(int offset){
	return (offset - get_offset_row(offset)*2*MAX_COLS) /2;
}

int get_cursor(){
	// so we set the control register to 15 which
	// lets us read the higher byte of cursor pos
	// then the same for 14/lower byte
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL,15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset*2;
}

void set_cursor(int offset){
	offset /= 2;
	// set each byte individually
	// setting the control reg brings out the byte at data address
	// and then we can overwrite it
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff)); //mask
}

void clear_screen(){
	char *vga = VIDEO_ADDRESS;

	for(int i = 0; i < MAX_COLS*MAX_ROWS; i++){
		vga[i*2] = ' ';
		vga[i*2+1] = WHITE_ON_BLACK;
	}
	set_cursor(get_screen_offset(0,0));
}
