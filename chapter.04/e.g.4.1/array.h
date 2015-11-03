/*
 * array.h
 *
 *  Created on: Nov 2, 2015
 *      Author: lidq
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "typedef.h"

//最大维度
#define MAX_DIM		(8)

typedef struct
{
	//数组基地址
	void *addr_base;
	//每个维度的大小
	int *addr_bounds;
	//每个维度具有最大元素数
	int *addr_counts;
	//维度
	int dim;
	//元素大小
	int ele_size;
	//元素个数
	int ele_count;
	//用于释放节点数据的回调函数
	void (*free_data)();
	//用于访问节点数据内容的回调函数
	void (*visit_data)();
} array;

//初始化数组
bool array_init(array *arr, void (*free_data)(), void (*visit_data)(), int dim, int ele_size, ...);

//销毁数组
bool array_destroy(array *arr);

//为数组中指定索引的元素赋值
bool array_setValue(array *arr, void *element, ...);

//取得数组中指定索引的元素值
bool array_getValue(array *arr, void *element, ...);

//遍历数组访问所有元素
bool array_visit(array *arr);

#endif /* ARRAY_H_ */
