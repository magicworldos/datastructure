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

//初始化数组
bool array_init(array *arr, void (*free_data)(), void (*visit_data)(), int dim, int ele_size, ...)
{
	if (arr == null)
	{
		return false;
	}

	if (dim > MAX_DIM)
	{
		return false;
	}

	//维度
	arr->dim = dim;
	//元素大小
	arr->ele_size = ele_size;
	//释放元素的回调函数
	arr->free_data = free_data;
	//访问元素的回调函数
	arr->visit_data = visit_data;
	//按维度申请每个维度最大值
	arr->addr_bounds = malloc(sizeof(int) * dim);
	if (arr->addr_bounds == null)
	{
		return false;
	}
	//按维度申请每个维度最大值
	arr->addr_counts = malloc(sizeof(int) * dim);
	if (arr->addr_counts == null)
	{
		return false;
	}

	//动态参数
	va_list ap;
	va_start(ap, ele_size);
	//计算总元素数量
	arr->ele_count = 1;
	for (int i = 0; i < dim; ++i)
	{
		//接收参数，每个维度数
		arr->addr_bounds[i] = va_arg(ap, int);
		//计算元素总数
		arr->ele_count *= arr->addr_bounds[i];
	}
	va_end(ap);

	//计算每个维度所有的元素数量
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

	//申请元素内存基地址
	arr->addr_base = malloc(ele_size * arr->ele_count);

	if (arr->addr_base == null)
	{
		free(arr->addr_bounds);
		free(arr->addr_counts);
		return false;
	}

	return true;
}

//销毁数组
bool array_destroy(array *arr)
{
	if (arr == null)
	{
		return true;
	}

	//释放元素
	if (arr->free_data != null)
	{
		for (int i = 0; i < arr->ele_count; ++i)
		{
			//通过回调函数释放元素所在内存
			void *p_del = arr->addr_base + arr->ele_size * i;
			arr->free_data(p_del);
		}
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

//为数组中指定索引的元素赋值
bool array_setValue(array *arr, void *element, ...)
{
	if (arr == null)
	{
		return false;
	}

	int index = 0;

	va_list ap;
	va_start(ap, element);

	//根据每个维度的索引号计算元素在内存中的线性索引
	for (int i = 0; i < arr->dim; ++i)
	{
		int k = va_arg(ap, int);
		//维度索引不能超过此维度的最大值
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
		//维度索引超过此维度的最大值，失败
		else
		{
			va_end(ap);
			return false;
		}
	}
	va_end(ap);

	//设置元素内容
	memcpy(arr->addr_base + arr->ele_size * index, element, arr->ele_size);

	return true;
}

//取得数组中指定索引的元素值
bool array_getValue(array *arr, void *element, ...)
{
	if (arr == null)
	{
		return false;
	}

	int index = 0;

	va_list ap;
	va_start(ap, element);

	//根据每个维度的索引号计算元素在内存中的线性索引
	for (int i = 0; i < arr->dim; ++i)
	{
		int k = va_arg(ap, int);
		//维度索引不能超过此维度的最大值
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
		//维度索引超过此维度的最大值，失败
		else
		{
			va_end(ap);
			return false;
		}
	}
	va_end(ap);

	//取得元素内容
	memcpy(element, arr->addr_base + arr->ele_size * index, arr->ele_size);

	return true;
}

//遍历数组访问所有元素
bool array_visit(array *arr)
{
	if (arr == null)
	{
		return false;
	}

	if (arr->visit_data == null)
	{
		return false;
	}

	//根据元素总个数遍历
	for (int i = 0; i < arr->ele_count; ++i)
	{
		//显示元素内容
		void *p_del = arr->addr_base + arr->ele_size * i;
		arr->visit_data(p_del);
	}

	return true;
}
