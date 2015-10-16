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

//定义操作符
char opers[7] =
{ '+', '-', '*', '/', '(', ')', '#' };

// 定义操作符的运算优先级
char oper_rule[7][7] =
{
// +
        '>', '>', '<', '<', '<', '>', '>',
        // -
        '>', '>', '<', '<', '<', '>', '>',
        // *
        '>', '>', '>', '>', '<', '>', '>',
        // /
        '>', '>', '>', '>', '<', '>', '>',
        // (
        '<', '<', '<', '<', '<', '=', ' ',
        // )
        '>', '>', '>', '>', ' ', '>', '>',
        // #
        '<', '<', '<', '<', '<', ' ', '=' };

//计算操作符优先级
char get_oper_rule(char operL, char operR)
{
	int i = 0;
	int j = 0;
	//取得左侧操作符下标
	for (; i < 7; i++)
	{
		if (opers[i] == operL)
		{
			break;
		}
	}
	//取得右侧操作符下标
	for (; j < 7; j++)
	{
		if (opers[j] == operR)
		{
			break;
		}
	}
	//返回优先级
	return oper_rule[i][j];
}

//根据操作符和操作数做计算
int operate(int a, int b, char oper)
{
	int result = 0;
	switch (oper)
	{
		case '+':
			result = a + b;
			break;

		case '-':
			result = a - b;
			break;

		case '*':
			result = a * b;
			break;

		case '/':
			result = a / b;
			break;
	}
	return result;
}

void free_char(char *ch)
{
	free(ch);
}

void free_int(int *i)
{
	free(i);
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

		int len = strlen(str);
		str[len] = '#';
		str[len + 1] = '\0';
		//构建栈
		s_stack stack_oper;
		s_stack stack_num;

		stack_init(&stack_oper, free_char);
		stack_init(&stack_num, free_int);

		char *ch_i = (char *) malloc(1);
		*ch_i = '#';
		stack_push(&stack_oper, ch_i);

		char *p = str;
		while (*p != '\0')
		{
			//如果是操作符则入操作符栈或计算
			if (*p == '#' || *p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')')
			{
				//栈顶元素出栈做比较
				char *ch;
				stack_pop(&stack_oper, &ch);

				//与当然操作符做优先级比较
				char oper_rule_re = get_oper_rule(*ch, *p);
				//优先级低，入操作符栈
				if (oper_rule_re == '<')
				{
					stack_push(&stack_oper, ch);
					ch = (char *) malloc(1);
					*ch = *p;
					stack_push(&stack_oper, ch);
					p++;
				}
				//优先级相同，去括号
				else if (oper_rule_re == '=')
				{
					//如果是#则结束
					if (*ch == '#')
					{
						free_char(ch);
						break;
					}
					free_char(ch);
					p++;
				}
				//优先级高，计算操作数并将结果入栈
				else if (oper_rule_re == '>')
				{
					int *numA;
					int *numB;
					int *numR = (int *) malloc(sizeof(int));
					stack_pop(&stack_num, &numA);
					stack_pop(&stack_num, &numB);
					*numR = operate(*numB, *numA, *ch);
					stack_push(&stack_num, numR);

					free_char(ch);
					free_int(numA);
					free_int(numB);
				}
			}
			//如果是数字则入数字栈
			else
			{
				//将字符串中的数据转为int型
				int i = 0;
				int *num = (int *) malloc(sizeof(int));
				for (; p[i] >= 48 && p[i] <= 57; i++)
				{
					if (i == 0)
					{
						*num = (int) p[i] - 48;
					}
					else
					{
						*num *= 10;
						*num += (int) p[i] - 48;
					}
				}
				//数字入栈
				stack_push(&stack_num, num);
				p += i;
			}
		}

		//显示最终运算结果
		int *numR;
		stack_pop(&stack_num, &numR);
		printf("Result is %d.\n", *numR);

		//销毁栈
		stack_destroy(&stack_oper);
		stack_destroy(&stack_num);

	}
	while (1);

	free(str);

	return 0;
}
