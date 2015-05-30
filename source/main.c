#include <interpreter.h>
#include <io.h>

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
				case 'i': interactive_mode = 1; break;
				case 'b': buffered_input = 1; break;
				case 'n': io_by_value = 1; break;
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


