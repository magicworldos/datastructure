#include <stdio.h>
#include "string.h"

int main(int argc, char **args)
{
	//字符串模式匹配
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


	//字符串替换
	char str[30];
	str_copy(str, "Hello WorlD WorlS World!");
	str_replace(str, "or", "BM");
	printf("%s\n", str);


	return 0;
}
