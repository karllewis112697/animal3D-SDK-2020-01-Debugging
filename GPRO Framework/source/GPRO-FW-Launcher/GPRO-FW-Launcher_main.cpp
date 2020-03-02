// GPRO-FW-Launcher.c/.cpp

#include <stdio.h>
#include <Windows.h>

#include "_general/_macros.h"

// custom debug print; a macro that both EXECUTES and PRINTS a line of code
#if (defined _DEBUG || defined DEBUG)
// executes the line of code	// prints the line of code
#define LINE(line) line\
	printf("\nTEXT: %s\nFILE: %s\nLINE #: %u\n",\
		 token_str(line),		\
		__FILE__,				\
		__LINE__				\
	); Sleep(1000) 
#else // NDEBUG
#define LINE (line) line
#endif // _DEBUG || DEBUG

class cExeption
{
	cExeption()
	{
		// setup print stuff
	}
public:
	void print()
	{
		// display
	}
};

int main()
{
	printf("\n\nBEGINNING OF MAIN \n\n");

	int test = 3;
	LINE(
		test = 7;
	);

	try {
		test = 42;
	}
	catch (cExeption e)
	{
		e.print();
	}

	printf("\n %d \n", test);

	printf("\n\nEND OF MAIN\n\n");

	system("pause");
}
