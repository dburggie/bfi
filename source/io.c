#include <stdio.h>

#include <io.h>


unsigned char get()
{
	static int closed = 0;

	unsigned char c = 0x00;

	if (closed)
	{
		return 0x00;
	}

	if (EOF == fscanf(stdin, "%c", &c))
	{
		closed = 1;
	}

	return c;
}

void put(unsigned char c)
{
	fprintf(stdout, "%c", c);
	fflush(stdout);
}
