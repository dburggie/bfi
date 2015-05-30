#include <interpreter.h>
#include <io.h>

int interpreter(const char const * code)
{
	unsigned char buf[30000] = { 0 };
	int i = 0, p = 0;

	int loop;

	while (code[i])
	{
		switch (code[i])
		{
			case '>':
				p++;
				if (p == 30000) return 1;
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
				buf[p] = get();
				break;

			case '.': 
				put(buf[p]);
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



