#include <interpreter.h>
#include <io.h>

static void help_dialog();

int main(const int argc, const char const *argv[])
{
	if (argc < 2) return 1;

	int i = 0;

	if (argv[1][0] == '-')
	{
		//read command line options
		for (i = 1; argv[1][i] != '\0'; i++)
		{
			switch (argv[1][i])
			{
				case 'h':
					help_dialog();
					return 0;
				case 'n':
					printf("Selecting Interactive Mode\n");
					interactive_mode = 1; 
					break;
				case 'i':
					printf("Selecting Input-By-Value Mode\n");
					input_by_value = 1;
					break;
				case 'o':
					printf("Selecting Output-By-Value Mode\n");
					output_by_value = 1;
					break;
				default: return 1;
			}
		}
	}

	if (interactive_mode)
	{
		return cli();
	}
	
	else
	{
		const char const * code = readFile(argv[argc - 1]);
		if (!code) return 1;
		return interpreter(code);
	}
}


static void help_dialog()
{
	printf("\n  Usage:\n    bfi -n[i][o]\n    bfi -[i][o] filename.bf\n\n");
}
