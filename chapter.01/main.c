/*
 * main.c
 *
 *  Created on: Sep 25, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void print_int(void *data)
{
	printf("%d\n", *((int *) data));
}

int main(int argc, char **args)
{
	s_list list;

	init_list(&list, sizeof(int));

	for (int i = 100; i < 110; ++i)
	{
		int *e = (int *)malloc(sizeof(int));
		*e = i;
		list_insert(&list, 0, e);
	}

	list_visit(&list, print_int);

	return 0;
}
