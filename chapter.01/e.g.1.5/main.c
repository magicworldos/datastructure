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

int main(int argc, char **args)
{
	//构建多项式A
	s_list listA;
	init_list(&listA);
	list_insert(&listA, 0, 4);
	list_insert(&listA, 1, 5);
	list_insert(&listA, 2, 6);
	list_insert(&listA, 4, -8);
	list_insert(&listA, 5, 3);
	list_insert(&listA, 7, -7);
	list_display(&listA);

	printf("\n");

	//构建多项式B
	s_list listB;
	init_list(&listB);
	list_insert(&listB, 0, 9);
	list_insert(&listB, 1, -3);
	list_insert(&listB, 2, -1);
	list_insert(&listB, 3, 3);
	list_insert(&listB, 5, -7);
	list_insert(&listB, 8, 3);
	list_display(&listB);

	printf("\n");

	s_list listC;
	init_list(&listC);
	list_add(&listA, &listB, &listC);
	list_display(&listC);

	//销毁list
	destroy_list(&listA);
	destroy_list(&listB);
	destroy_list(&listC);

	return 0;
}
