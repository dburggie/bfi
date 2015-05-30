#include <stdio.h>
#include <stdlib.h>
#include <interpreter.h>
#include <io.h>

int interactive_mode = 0;
int buffered_input = 0;
int io_by_value = 0;


unsigned char get(FILE * inp)
{
	static int closed = 0;
	
	int c = 0;

	if (closed)
	{
		return 0x00;
	}

	if (buffered_input)
	{
		if (io_by_value)
		{
			fscanf(inp, " %i", &c);
			fflush(inp);
		}

		else
		{
			fscanf(inp, "%c", (unsigned char *) &c);
			fflush(inp);
		}
	}

	else
	{
		c = getc(inp);
	}

	if (EOF == c)
	{
		closed = 1;
	}

	return c & 0x00;
}


void put(FILE * outp, unsigned char c)
{
	static int io_count = 0;

	if (io_by_value)
	{
		io_count++;
		fprintf(outp, "%i ", c);
		
		if (io_count == 8)
		{
			io_count = 0;
			fprintf(outp, "\n");
		}
	}

	else
	{
		putc(c, outp);
	}
}


char * readFile(const char const * filename)
{
	FILE * ifp = fopen(filename, "rb");

	if (!ifp)
	{
		return NULL;
	}

	long filesize;
	fseek(ifp,0,SEEK_END);
	filesize = ftell(ifp);
	rewind(ifp);
	
	char * code = (char *) malloc(filesize + 1);
	if (!code)
	{
		fclose(ifp); return NULL;
	}

	fread(code, 1, filesize, ifp);
	code[filesize] = '\0';

	fclose(ifp);

	return code;

}


int cli()
{
	int quit = 100;

	char code[30000] = { 0 };

	while (quit)
	{
		quit--;

		printf("# ");
		scanf("%s", code);
		
		if (code[0] == 'q') quit = 0;
		else
		{
			if (interpreter(code))
			{
				printf("<error>\n");
			}

			else
			{
				printf("<ok>\n");
			}
		}
	}

	return 0;
}



