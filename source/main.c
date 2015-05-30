#include <interpreter.h>
#include <readFile.h>

int main(const int argc, const char const *argv[])
{
	if (argc != 2) return 1;

	const char const * code = readFile(argv[1]);

	if (!code) return 1;

	return interpreter(code);
}


