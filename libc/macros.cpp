#include "macros.h"
#include "../drivers/screen.h"
#include "string.h"

void panic(char *msg, int line, char* file) {
    kprint("Error on line ");
    char s[10]; int_to_ascii(line,s);
    kprint(s);
    kprint(" in file "); 
    kprint(file);
    kprint("\nError message:\n");
    kprint(msg);
    while(1);
}