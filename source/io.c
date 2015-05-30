#include <stdio.h>
#include <stdlib.h>
#include <interpreter.h>
#include <io.h>

int interactive_mode = 0;
int input_by_value = 0;
int output_by_value = 0;


unsigned char get(FILE * inp)
{
	static int closed = 0;
	
	int c = 0;
	int err = 0;

	if (closed)
	{
		return 0x00;
	}

	if (input_by_value)
	{
		while (0 == (err = fscanf(inp," %i", &c)))
		{
			if (EOF == err) 
			{
				closed = 1;
				c = 0;
				break;
			}
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

	return c & 0xff;
}


void put(FILE * outp, unsigned char c)
{
	static int io_count = 0;

	if (output_by_value)
	{
		io_count++;
		fprintf(outp, "%3.i ", c);
		
		if (io_count == 8)
		{
			io_count = 0;
			fprintf(outp, "\n");
		}
	}

	else
	{
		fprintf(outp,"%c",c);
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
	printf("(\'q\' to quit)\n");

	int quit = 100;

	char code[30000] = { 0 };

	while (quit)
	{
		quit--;

		printf("# ");
		fgets(code,30000,stdin);
		
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



