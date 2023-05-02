#pragma once


#define PANIC(msg) panic(msg ,__LINE__,__FILE__)

void panic(char *msg, int line, char* file);
