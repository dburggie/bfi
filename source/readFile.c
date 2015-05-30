#include <stdio.h>
#include <stdlib.h>
#include <readFile.h>

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
