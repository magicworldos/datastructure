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
bool init_list(s_list *list, int ele_size)
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
	s_node *p_ele = (s_node *) malloc(sizeof(s_node));
	if (p_ele == null)
	{
		return false;
	}
	p_ele->data = (s_node *) malloc(list->ele_size);
	if (p_ele->data == null)
	{
		return false;
	}
	list->length++;
	//移动后续元素次数
	int move_times = list->length - i;
	//复制e元素的内容到第i个元素中
	memcpy(p_ele->data, e, list->ele_size);
	s_node temp;
	s_node temp2;
	//复制e元素的内容到第i个元素中
	memcpy(&temp, p_ele, sizeof(s_node));
	for (int j = 0; j < move_times; ++j)
	{
		//计算元素位置
		s_node *node = (s_node *) ((char *) list->header + ((i + j) * sizeof(s_node)));
		//复制第i个元素到temp中
		memcpy(&temp2, node, sizeof(s_node));
		//复制e元素的内容到第i个元素中
		memcpy(node, &temp, sizeof(s_node));
		//复制temp2到temp中
		memcpy(&temp, &temp2, sizeof(s_node));
	}
	return true;
}

//删除第i个元素
bool list_delete(s_list *list, int i)
{
	return false;
}

//对每个元素执行visit操作
bool list_visit(s_list *list, void (*visit)(void *data))
{
	if (list == null || list->header == null)
	{
		return false;
	}
	for (int i = 0; i < list->length; ++i)
	{
		//计算元素位置
		s_node *node = (s_node *) ((char *) list->header + (i * sizeof(s_node)));
		visit(node->data);
	}

	return true;
}
