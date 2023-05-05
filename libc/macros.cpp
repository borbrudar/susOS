#include "macros.h"
#include "../drivers/screen.h"
#include "string.h"

void panic(const char *msg, int line, const char* file) {
    kprint("Error on line ");
    char s[10]; int_to_ascii(line,s);
    kprint(s);
    kprint(" in file "); 
    kprint(file);
    kprint("\nError message:\n");
    kprint(msg);
    while(1);
}


void assert(const char *msg, int line, const char *file){
    kprint("Assertion: "); 
    kprint(msg); kprint(" failed on line ");
    char s[5]; int_to_ascii(line,s);
    kprint(s);kprint(" in file ");
    kprint(file); kprint("\n");
    while(1);
}