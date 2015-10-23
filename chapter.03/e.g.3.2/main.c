#include <stdio.h>
#include "string.h"

int main(int argc, char **args)
{
	int ind = -1;

	ind = str_index("Hello WorlD WorlS World!", "World", 0);
	printf("%d\n", ind);

	ind = str_index("Hello WorlD WorlS World!", "Worl", 0);
	printf("%d\n", ind);

	ind = str_index("Hello WorlD WorlS World!", "Worl", 7);
	printf("%d\n", ind);

	ind = str_index("Hello WorlD WorlS World!", "Worl", 15);
	printf("%d\n", ind);

	ind = str_index("Hello WorlD WorlS World!", "WorlT", 0);
	printf("%d\n", ind);

	return 0;
}
