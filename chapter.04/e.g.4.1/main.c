#include <stdio.h>
#include "array.h"

#define DIM (3)
#define M (9)
#define N (4)
#define O (3)

int main(int argc, char **args)
{
	array arr_int;
	array_init(&arr_int, DIM, sizeof(int), M, N, O);

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

	array_destroy(&arr_int);

	printf("\n");

	//double类型
	array arr_double;
	array_init(&arr_double, DIM, sizeof(double), M, N, O);

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

	array_destroy(&arr_double);

	return 0;
}
