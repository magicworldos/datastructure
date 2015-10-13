/*
 * main.c
 *
 *  Created on: Sep 25, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void free_int(void *data)
{
	free(data);
}

void print_int(void *data)
{
	printf("%d\n", *((int *) data));
}

typedef struct
{
	int no;
	int age;
	char *name;
} student;

void print_stu(void *data)
{
	student *stu = (student *) data;
	printf("no:%d age:%d name:%s\n", stu->no, stu->age, stu->name);
}

void free_stu(void *data)
{
	student *stu = (student *) data;
	free(stu->name);
	free(stu);
}

int main(int argc, char **args)
{
	//用于存放int型数据的list
	s_list list_int;
	//释放内存函数与访问函数均是int型
	init_list(&list_int, sizeof(int), free_int, print_int);
	//插入数据
	for (int i = 0; i < 5; ++i)
	{
		int *e = (int *) malloc(sizeof(int));
		*e = i;
		list_insert(&list_int, 0, e);
	}
	//显示list中所有数据内容
	list_visit(&list_int);
	//销毁list
	destroy_list(&list_int);

	printf("\n");

	//用于存放student型数据的list
	s_list list_stu;
	//释放内存函数与访问函数均是student型
	init_list(&list_stu, sizeof(student), free_stu, print_stu);

	//插入数据
	student *stu1 = (student *) malloc(sizeof(student));
	stu1->no = 15100101;
	stu1->age = 23;
	stu1->name = (char *) malloc(20);
	memcpy(stu1->name, "lidq", 20);
	list_insert(&list_stu, 0, stu1);
	//插入数据
	student *stu2 = (student *) malloc(sizeof(student));
	stu2->no = 15100102;
	stu2->age = 21;
	stu2->name = (char *) malloc(20);
	memcpy(stu2->name, "zhaoy", 20);
	list_insert(&list_stu, 1, stu2);
	//插入数据
	student *stu3 = (student *) malloc(sizeof(student));
	stu3->no = 15100103;
	stu3->age = 22;
	stu3->name = (char *) malloc(20);
	memcpy(stu3->name, "liuzh", 20);
	list_insert(&list_stu, 2, stu3);

	//显示list中所有内容
	list_visit(&list_stu);

	//销毁list
	destroy_list(&list_stu);

	return 0;
}
