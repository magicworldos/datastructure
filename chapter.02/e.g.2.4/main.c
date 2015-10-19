/*
 * main.c
 *
 *  Created on: Sep 25, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

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
	//用于存放int型数据的队列
	s_queue queue_int;
	//释放内存函数与访问函数均是int型
	init_queue(&queue_int, sizeof(int), free_int, print_int);
	//插入数据
	for (int i = 0; i < 5; ++i)
	{
		int *e = (int *) malloc(sizeof(int));
		*e = i;
		queue_insert(&queue_int, e);
	}
	//显示queue中所有数据内容
	queue_visit(&queue_int);
	//销毁queue
	destroy_queue(&queue_int);

	printf("\n");

	//用于存放student型数据的queue
	s_queue queue_stu;
	//释放内存函数与访问函数均是student型
	init_queue(&queue_stu, sizeof(student), free_stu, print_stu);

	//在队列尾插入数据
	student *stu1 = (student *) malloc(sizeof(student));
	stu1->no = 15100101;
	stu1->age = 23;
	stu1->name = (char *) malloc(20);
	memcpy(stu1->name, "lidq", 20);
	queue_insert(&queue_stu, stu1);
	//在队列尾插入数据
	student *stu2 = (student *) malloc(sizeof(student));
	stu2->no = 15100102;
	stu2->age = 21;
	stu2->name = (char *) malloc(20);
	memcpy(stu2->name, "zhaoy", 20);
	queue_insert(&queue_stu, stu2);
	//在队列尾插入数据
	student *stu3 = (student *) malloc(sizeof(student));
	stu3->no = 15100103;
	stu3->age = 22;
	stu3->name = (char *) malloc(20);
	memcpy(stu3->name, "liuzh", 20);
	queue_insert(&queue_stu, stu3);

	//显示队列中所有内容
	queue_visit(&queue_stu);

	printf("\n");

	//在队列头删除元素
	queue_delete(&queue_stu);
	//显示队列中所有内容
	queue_visit(&queue_stu);

	//销毁队列
	destroy_queue(&queue_stu);

	return 0;
}
