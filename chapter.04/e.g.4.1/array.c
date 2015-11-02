/*
 * array.c
 *
 *  Created on: Nov 2, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

bool array_init(array *arr, int dim, int ele_size, ...)
{
	if (arr == null)
	{
		return false;
	}

	if (dim > MAX_DIM)
	{
		return false;
	}

	arr->dim = dim;
	arr->ele_size = ele_size;

	arr->addr_bounds = malloc(sizeof(int) * dim);
	if (arr->addr_bounds == null)
	{
		return false;
	}

	arr->addr_counts = malloc(sizeof(int) * dim);
	if (arr->addr_counts == null)
	{
		return false;
	}

	va_list ap;
	va_start(ap, ele_size);
	int count = 1;
	for (int i = 0; i < dim; ++i)
	{
		arr->addr_bounds[i] = va_arg(ap, int);
		count *= arr->addr_bounds[i];
	}
	va_end(ap);

	for (int i = dim - 1; i >= 0; --i)
	{
		if (i == dim - 1)
		{
			arr->addr_counts[i] = arr->addr_bounds[i];
		}
		else
		{
			arr->addr_counts[i] = arr->addr_counts[i + 1] * arr->addr_bounds[i];
		}
	}

	arr->addr_base = malloc(ele_size * count);

	if (arr->addr_base == null)
	{
		free(arr->addr_bounds);
		free(arr->addr_counts);
		return false;
	}

	return true;
}

bool array_destroy(array *arr)
{
	if (arr == null)
	{
		return true;
	}

	if (arr->addr_bounds != null)
	{
		free(arr->addr_bounds);
	}

	if (arr->addr_counts != null)
	{
		free(arr->addr_counts);
	}

	if (arr->addr_base != null)
	{
		free(arr->addr_base);
	}

	return true;
}

bool array_setValue(array *arr, void *element, ...)
{
	if (arr == null)
	{
		return false;
	}

	int index = 0;

	va_list ap;
	va_start(ap, element);

	for (int i = 0; i < arr->dim; ++i)
	{
		int k = va_arg(ap, int);
		if (0 <= k && k < arr->addr_bounds[i])
		{
			if (i < arr->dim - 1)
			{
				index += k * arr->addr_counts[i + 1];
			}
			else
			{
				index += k;
			}
		}
		else
		{
			va_end(ap);
			return false;
		}
	}
	va_end(ap);

	memcpy(arr->addr_base + arr->ele_size * index, element, arr->ele_size);

	return true;
}

bool array_getValue(array *arr, void *element, ...)
{
	if (arr == null)
	{
		return false;
	}

	int index = 0;

	va_list ap;
	va_start(ap, element);

	for (int i = 0; i < arr->dim; ++i)
	{
		int k = va_arg(ap, int);
		if (0 <= k && k < arr->addr_bounds[i])
		{
			if (i < arr->dim - 1)
			{
				index += k * arr->addr_counts[i + 1];
			}
			else
			{
				index += k;
			}
		}
		else
		{
			va_end(ap);
			return false;
		}
	}
	va_end(ap);

	memcpy(element, arr->addr_base + arr->ele_size * index, arr->ele_size);

	return true;
}
