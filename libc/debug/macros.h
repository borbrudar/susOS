#pragma once


#define PANIC(msg) panic(msg ,__LINE__,__FILE__)
#define ASSERT(EX) (void)((EX) || (assert(#EX,__LINE__,__FILE__),0));

void panic(const char *msg, int line, const char* file);
void assert(const char *msg, int line, const char *file);