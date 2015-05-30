#include <stdio.h>
#include <interpreter.h>
#include <io.h>

#define BUFSIZE 30000

int interpreter(const char const * code)
{
	unsigned char buf[BUFSIZE] = { 0 };
	int i = 0, p = 0;

	int loop;

	while (code[i])
	{
		switch (code[i])
		{
			case '>':
				p++;
				if (p == BUFSIZE) return 1;
				break;

			case '<':
				p--;
				if (p < 0) return 1;
				break;

			case '+':
				buf[p]++;
				break;

			case '-':
				buf[p]--;
				break;

			case ',':
				buf[p] = get(stdin);
				break;

			case '.': 
				put(stdout,buf[p]);
				break;

			case '[':
				if (!buf[p])
				{
					loop = 1;
					while (loop > 0)
					{
						i++;
						switch (code[i])
						{
							case '[': loop++; break;
							case ']': loop--; break;
							default: break;
						}
					}
				}
				break;

			case ']':
				if (buf[p])
				{
					loop = 1;
					while (loop > 0)
					{
						i--;
						switch (code[i])
						{
							case '[': loop--; break;
							case ']': loop++; break;
							default: break;
						}
					}
				}
				break;

			default: break;
		}

		i++;
	}

	return 0;
}



