/*
 * main.c
 *
 *  Created on: Sep 25, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void free_int(void *data)
{
	free(data);
}

void print_int(void *data)
{
	printf("%d\n", *((int *) data));
}

int main(int argc, char **args)
{
	s_list list;

	init_list(&list, sizeof(int), free_int, print_int);

	for (int i = 0; i < 20; ++i)
	{
		int *e = (int *) malloc(sizeof(int));
		*e = i;
		list_insert(&list, 0, e);
	}

	list_visit(&list);

	destroy_list(&list);

	return 0;
}
