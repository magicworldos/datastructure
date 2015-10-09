/*
 * list.c
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//构建一个顺序线性表
bool init_list(s_list *list, int ele_size, void (*free_data)(), void (*visit_data)())
{
	if (list == null)
	{
		return false;
	}
	//申请数据所在的内存空间
	list->header = malloc(sizeof(s_node) * INIT_SIZE);
	if (list->header == null)
	{
		return false;
	}
	list->ele_size = ele_size;
	list->size = INIT_SIZE;
	list->length = 0;
	list->free_data = free_data;
	list->visit_data = visit_data;
	return true;
}

//销毁表
bool destroy_list(s_list *list)
{
	if (list == null)
	{
		return false;
	}

	if (list->header == null)
	{
		return true;
	}

	clear_list(list);

	free(list->header);

	return true;
}

//清空表中所有元素
bool clear_list(s_list *list)
{
	if (list == null || list->header == null)
	{
		return false;
	}

	for (int i = 0; i < list->length; ++i)
	{
		//计算元素位置
		s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
		list->free_data(node->data);
	}

	list->length = 0;

	return true;
}

//取得表中现有元素个数
int list_length(s_list *list)
{
	if (list == null)
	{
		return 0;
	}

	return list->length;
}

//取得在第i个位置元素的数据内容
bool get_element(s_list *list, int i, void *e)
{
	if (list == null || list->header == null || e == null)
	{
		return false;
	}

	//计算元素位置
	s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
	//复制元素数据到e中
	memcpy(e, node->data, list->ele_size);

	return true;
}

//在第i个位置前插入一个新元素
bool list_insert(s_list *list, int i, void *e)
{
	if (list == null || list->header == null || e == null)
	{
		return false;
	}

	if (i != 0 && i >= list->length)
	{
		return false;
	}

	//超过当前最大容量，请申原容量的2倍
	if (list->length + 1 > list->size)
	{
		//申请新空间
		void *p = realloc(list->header, list->size * sizeof(s_node) * 2);
		if (p == null)
		{
			return false;
		}
		list->header = p;
		list->size *= 2;
	}

	//创建新节点
	s_node *p_ele = (s_node *) malloc(sizeof(s_node));
	if (p_ele == null)
	{
		return false;
	}
	//数据
	p_ele->data = e;

	//从尾到i依次向后移动一个单元
	for (int j = list->length; j > i; --j)
	{
		s_node *node_pre = (s_node *) ((char *) list->header + ((j - 1) * sizeof(s_node)));
		s_node *node_curr = (s_node *) ((char *) list->header + (j * sizeof(s_node)));
		memcpy(node_curr, node_pre, sizeof(s_node));
	}

	//插入新元素
	s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
	memcpy(node, p_ele, sizeof(s_node));

	//长度加1
	list->length++;

	return true;
}

//删除第i个元素
bool list_delete(s_list *list, int i)
{
	if (list == null || list->header == null)
	{
		return false;
	}

	if (i >= list->length)
	{
		return false;
	}

	//计算元素位置
	s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
	list->free_data(node->data);
	//从i+1依次向前移动一个单元
	for (int j = i; j < list->length - 1; ++j)
	{
		s_node *node_curr = (s_node *) ((char *) list->header + (j * sizeof(s_node)));
		s_node *node_next = (s_node *) ((char *) list->header + ((j + 1) * sizeof(s_node)));
		memcpy(node_curr, node_next, sizeof(s_node));
	}
	list->length--;

	return true;
}

//对每个元素执行visit操作
bool list_visit(s_list *list)
{
	if (list == null || list->header == null)
	{
		return false;
	}
	for (int i = 0; i < list->length; ++i)
	{
		//计算元素位置
		s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
		list->visit_data(node->data);
	}

	return true;
}
