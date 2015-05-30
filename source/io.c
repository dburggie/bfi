#include <stdio.h>
#include <io.h>

unsigned char get(FILE * inp)
{
	static int closed = 0;

	int c = 0;

	if (closed)
	{
		return 0x00;
	}

	c = getc(inp);

	if (EOF == c)
	{
		closed = 1;
	}

	return c & 0x00;
}

void put(FILE * outp, unsigned char c)
{
	fprintf(outp, "%c", c);
	fflush(outp);
}
