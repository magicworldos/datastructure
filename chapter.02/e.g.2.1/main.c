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

//释放int类型
void free_int(void *data)
{
	free(data);
}

//学生结构体
typedef struct
{
	int no;
	int age;
	char *name;
} student;

//创建学生
student *create_stu(int no, int age, const char* name)
{
	student *stu = (student *) malloc(sizeof(student));
	stu->no = no;
	stu->age = age;
	stu->name = (char *)malloc(20);
	memcpy(stu->name, name, 20);
	return stu;
}

//释放学生
void free_stu(void *data)
{
	student *stu = (student *) data;
	free(stu->name);
	free(stu);
}

//显示学生信息
void print_stu(student *stu)
{
	printf("no:%d age:%d name:%s\n", stu->no, stu->age, stu->name);
}

int main(int argc, char **args)
{
	//用于int类型的栈，回调函数为free_int
	s_stack s;
	stack_init(&s, free_int);
	//压栈5个元素
	for (int i = 0; i < 5; i++)
	{
		int *val = malloc(sizeof(int));
		*val = i;
		stack_push(&s, val);
	}
	//出栈3个元素
	for (int i = 0; i < 5; i++)
	{
		int *val;
		stack_pop(&s, &val);
		printf("%d\n", *val);
		free_int(val);
	}
	//销毁栈
	stack_destroy(&s);

	//用于存放human类型的栈，回调函数为destructor_human
	s_stack s_stu;
	stack_init(&s_stu, free_stu);
	//插入数据
	student *stu1 = create_stu(15100101, 21, "lidq");
	stack_push(&s_stu, stu1);
	student *stu2 = create_stu(15100102, 22, "zhuwj");
	stack_push(&s_stu, stu2);
	student *stu3 = create_stu(15100103, 23, "baiy");
	stack_push(&s_stu, stu3);

	//循环出栈，出栈3个元素
	for (int i = 0; i < 3; i++)
	{
		student *stu;
		stack_pop(&s_stu, &stu);
		print_stu(stu);
		free_stu(stu);
	}
	//销毁栈
	stack_destroy(&s_stu);

	return 0;
}
