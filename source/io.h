#ifndef _IO_H
#define _IO_H

#include <stdio.h>

extern int interactive_mode;
extern int input_by_value;
extern int output_by_value;

unsigned char get(FILE * inp);
void put(FILE * outp, unsigned char c);

char * readFile(const char const * filename);
int cli();

#endif
