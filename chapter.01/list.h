/*
 * list.h
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "typedef.h"

#define INIT_SIZE (10)

//表节点
typedef struct
{
	void *data;
} s_node;

//表数据结构
typedef struct
{
	//元素大小
	int ele_size;
	//目前元素个数
	int length;
	//表总大小
	int size;
	//内存空间的首地址
	void *header;
} s_list;

//构建一个顺序线性表
bool init_list(s_list *list, int ele_size);

//销毁表
bool destroy_list(s_list *list);

//清空表中所有元素
bool clear_list(s_list *list);

//取得表中现有元素个数
int list_length(s_list *list);

//取得在第i个位置元素的数据内容
bool get_element(s_list *list, int i, void *e);

//在第i个位置前插入一个新元素
bool list_insert(s_list *list, int i, void *e);

//删除第i个元素
bool list_delete(s_list *list, int i);

//对每个元素执行visit操作
bool list_visit(s_list *list, void (*visit)(void *data));

#endif
