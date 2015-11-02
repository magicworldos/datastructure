/*
 * array.h
 *
 *  Created on: Nov 2, 2015
 *      Author: lidq
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "typedef.h"

#define MAX_DIM		(8)

typedef struct
{
	void *addr_base;
	int *addr_bounds;
	int *addr_counts;
	int ele_size;
	int dim;
} array;

bool array_init(array *arr, int dim, int ele_size, ...);

bool array_destroy(array *arr);

bool array_setValue(array *arr, void *element, ...);

bool array_getValue(array *arr, void *element, ...);

#endif /* ARRAY_H_ */
