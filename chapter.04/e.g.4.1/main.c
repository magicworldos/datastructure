#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

#define DIM (3)
#define M (9)
#define N (4)
#define O (3)

//学生数据结构
typedef struct
{
	int no;
	char *name;
	int age;
} student;

//访问int类型
void visit_int(int *p)
{
	printf("%d, ", *p);
}

//访问double类型
void visit_double(double *p)
{
	printf("%f, ", *p);
}

//访问student类型
void visit_student(student *p)
{
	if (p == null)
	{
		return;
	}

	if (p->name == null)
	{
		return;
	}

	printf("%d\t%s\t%d\t", p->no, p->name, p->age);
}

//释放student类型的函数
void free_student(student *p)
{
	if (p == null)
	{
		return;
	}

	if (p->name == null)
	{
		return;
	}

	free(p->name);
}

int main(int argc, char **args)
{
	//整型数组
	array arr_int;
	array_init(&arr_int, null, visit_int, DIM, sizeof(int), M, N, O);
	int e = 0;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < O; ++k)
			{
				array_setValue(&arr_int, &e, i, j, k);
				e++;
			}
		}
	}
	int v;
	for (int i = 0; i < M; ++i)
	{

		for (int j = 0; j < N; ++j)
		{
			printf("{");
			for (int k = 0; k < O; ++k)
			{
				array_getValue(&arr_int, &v, i, j, k);
				if (k < O - 1)
				{
					printf(" %3d,", v);
				}
				else
				{
					printf(" %3d", v);
				}
			}
			if (j < N - 1)
			{
				printf("}, ");
			}
			else
			{
				printf("} ");
			}
		}
		printf("\n");
	}
	printf("\n");
	array_visit(&arr_int);
	array_destroy(&arr_int);
	printf("\n");
	printf("\n");

	//浮点型数组
	array arr_double;
	array_init(&arr_double, null, visit_double, DIM, sizeof(double), M, N, O);
	double ed = 0;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < O; ++k)
			{
				array_setValue(&arr_double, &ed, i, j, k);
				ed += 0.09;
			}
		}
	}
	double vd;
	for (int i = 0; i < M; ++i)
	{

		for (int j = 0; j < N; ++j)
		{
			printf("{");
			for (int k = 0; k < O; ++k)
			{
				array_getValue(&arr_double, &vd, i, j, k);
				if (k < O - 1)
				{
					printf(" %6.2f,", vd);
				}
				else
				{
					printf(" %6.2f", vd);
				}
			}
			if (j < N - 1)
			{
				printf("}, ");
			}
			else
			{
				printf("} ");
			}
		}
		printf("\n");
	}
	printf("\n");
	array_visit(&arr_double);
	printf("\n");
	array_destroy(&arr_double);
	printf("\n");

	//结构体型数组
	array arr_student;
	array_init(&arr_student, free_student, visit_student, DIM, sizeof(student), 2, 2, 2);

	int name_max_len = 20;

	student stu0;
	stu0.no = 15051201;
	stu0.name = (char *) malloc(name_max_len);
	memcpy(stu0.name, "lidq", name_max_len);
	stu0.age = 23;
	array_setValue(&arr_student, &stu0, 0, 0, 0);

	student stu1;
	stu1.no = 15051202;
	stu1.name = (char *) malloc(name_max_len);
	memcpy(stu1.name, "baihq", name_max_len);
	stu1.age = 24;
	array_setValue(&arr_student, &stu1, 0, 0, 1);

	student stu2;
	stu2.no = 15051203;
	stu2.name = (char *) malloc(name_max_len);
	memcpy(stu2.name, "yangx", name_max_len);
	stu2.age = 25;
	array_setValue(&arr_student, &stu2, 0, 1, 0);

	student stu3;
	stu3.no = 15051204;
	stu3.name = (char *) malloc(name_max_len);
	memcpy(stu3.name, "yany", name_max_len);
	stu3.age = 23;
	array_setValue(&arr_student, &stu3, 0, 1, 1);

	student stu4;
	stu4.no = 15051205;
	stu4.name = (char *) malloc(name_max_len);
	memcpy(stu4.name, "shanc", name_max_len);
	stu4.age = 22;
	array_setValue(&arr_student, &stu4, 1, 0, 0);

	student stu5;
	stu5.no = 15051206;
	stu5.name = (char *) malloc(name_max_len);
	memcpy(stu5.name, "wangh", name_max_len);
	stu5.age = 21;
	array_setValue(&arr_student, &stu5, 1, 0, 1);

	student stu6;
	stu6.no = 15051207;
	stu6.name = (char *) malloc(name_max_len);
	memcpy(stu6.name, "caoj", name_max_len);
	stu6.age = 26;
	array_setValue(&arr_student, &stu6, 1, 1, 0);

	student stu7;
	stu7.no = 15051208;
	stu7.name = (char *) malloc(name_max_len);
	memcpy(stu7.name, "baiy", name_max_len);
	stu7.age = 23;
	array_setValue(&arr_student, &stu7, 1, 1, 1);

	student stu;
	for (int i = 0; i < 2; ++i)
	{

		for (int j = 0; j < 2; ++j)
		{
			printf("{");
			for (int k = 0; k < 2; ++k)
			{
				array_getValue(&arr_student, &stu, i, j, k);
				visit_student(&stu);
				printf(", ");
			}
			printf("}, ");
		}
		printf("\n");
	}
	printf("\n");
	array_visit(&arr_student);
	printf("\n");
	array_destroy(&arr_student);

	return 0;
}
