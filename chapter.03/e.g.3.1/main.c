#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main(int argc, char **args)
{
	char *str = (char *) malloc(100);

	str_copy(str, "Hello World!");
	printf("%s\n", str);

	int cmp0 = str_compare("abcde", "abcde");
	int cmp1 = str_compare("abcde", "abcdf");
	int cmp2 = str_compare("abcdf", "abcde");
	int cmp3 = str_compare("abcde", "abcdef");
	int cmp4 = str_compare("abcdef", "abcde");
	printf("%d %d %d %d %d\n", cmp0, cmp1, cmp2, cmp3, cmp4);

	str_concat(str, "Hello ", "World!");
	printf("%s\n", str);

	str_sub(str, "Hello World!", 7, 2);
	printf("%s\n", str);

	int ind0 = str_index("Hello World!", "o", 0);
	int ind1 = str_index("Hello World!", "o", 5);
	printf("%d %d\n", ind0, ind1);

	str_copy(str, "Hello World!");
	str_insert(str, "My Beautiful ", 6);
	printf("%s\n", str);

	str_delete(str, 6, 3);
	printf("%s\n", str);

	str_delete(str, 6, 10);
	printf("%s\n", str);

	free(str);

	return 0;
}
