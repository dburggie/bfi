#ifndef _IO_H
#define _IO_H

#include <stdio.h>

extern int interactive_mode;
extern int buffered_input;
extern int io_by_value;

unsigned char get(FILE * inp);
void put(FILE * outp, unsigned char c);

char * readFile(const char const * filename);
int cli();

#endif
