/*
 * main.c
 *
 *  Created on: Sep 25, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void free_char(char *ch)
{
	free(ch);
}

int main(int argc, char **args)
{
	char *str = (char *) malloc(200);
	do
	{
		printf("Please enter the expression(Enter \"exit\" to quit): ");
		scanf("%s", str);

		if (strcmp(str, "exit") == 0)
		{
			break;
		}

		//构建栈
		s_stack s;
		stack_init(&s, free_char);
		char *p = str;
		bool isValid = true;

		//遍历表达式
		while (*p != '\0')
		{
			//如果是左括号，入栈
			if (*p == '(' || *p == '[' || *p == '{')
			{
				char *ch = (char *) malloc(1);
				*ch = *p;
				stack_push(&s, ch);
			}
			//如果是右括号，出栈
			else if (*p == ')' || *p == ']' || *p == '}')
			{
				char *ch;
				if (s.ele_count == 0)
				{
					isValid = false;
					break;
				}

				stack_pop(&s, &ch);

				//左右括号匹配合法
				if ((*ch == '(' && *p == ')') || (*ch == '[' && *p == ']') || (*ch == '{' && *p == '}'))
				{
					free_char(ch);
				}
				//左右括号匹配非法
				else
				{
					free_char(ch);
					isValid = false;
					break;
				}
			}

			p++;

			if (*p == '\0' && s.ele_count > 0)
			{
				isValid = false;
				break;
			}
		}
		//销毁栈
		stack_destroy(&s);

		if (isValid)
		{
			printf("%s OK.\n", str);
		}
		else
		{
			printf("\"%s\" expression is invalid.\n", str);
		}
	}
	while (1);

	free(str);

	return 0;
}
