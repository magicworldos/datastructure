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
	list->ele_size = ele_size;
	list->length = 0;
	list->free_data = free_data;
	list->visit_data = visit_data;
	list->header = null;
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

	return true;
}

//清空表中所有元素
bool clear_list(s_list *list)
{
	if (list == null)
	{
		return false;
	}

	//从头节点开始释放
	s_node *p = list->header;
	while (p != null)
	{
		//释放内存
		list->free_data(p->data);
		s_node *t = p;
		p = p->next;
		free(t);
	}
	list->header = null;
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

	s_node *p = list->header;
	int j = 0;
	while (p != null)
	{
		//找到第i个元素
		if (j == i)
		{
			//复制元素数据到e中
			memcpy(e, p->data, list->ele_size);
			return true;
		}
		p = p->next;
		j++;
	}

	return false;
}

//在第i个位置前插入一个新元素
bool list_insert(s_list *list, int i, void *e)
{
	if (list == null || e == null)
	{
		return false;
	}

	if (i != 0 && i > list->length)
	{
		return false;
	}

	//申请新节点内存
	s_node *p_new = (s_node *) malloc(sizeof(s_node));
	p_new->data = e;
	p_new->next = null;

	//如果头节点为空
	if (i == 0)
	{
		//设置头节点为插入元素
		p_new->next = list->header;
		list->header = p_new;
		//长度加1
		list->length++;
		return true;
	}
	else
	{
		//在i-1与i之间位置插入
		s_node *p = list->header;
		int j = 0;
		while (p != null)
		{
			//找到第i-1个元素
			if (j == i - 1)
			{
				//插入新节点
				p_new->next = p->next;
				p->next = p_new;
				//长度加1
				list->length++;
				return true;
			}
			p = p->next;
			j++;
		}
	}

	return false;
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

	//如果是头节点
	if (i == 0)
	{
		//删除头节点
		list->header = list->header->next;
		//长度减1
		list->length--;
		return true;
	}
	else
	{
		s_node *p = list->header;
		int j = 0;
		while (p != null)
		{
			//找到第i-1个元素
			if (j == i - 1)
			{
				//删除第i个元素
				s_node *p_del = p->next;
				p->next = p_del->next;
				//释放内存
				list->free_data(p_del->data);
				free(p_del);
				//长度减1
				list->length--;
				return true;
			}
			p = p->next;
			j++;
		}
	}

	return false;
}

//对每个元素执行visit操作
bool list_visit(s_list *list)
{
	if (list == null || list->header == null)
	{
		return false;
	}

	//顺序访问每一个元素
	s_node *p = list->header;
	while (p != null)
	{
		list->visit_data(p->data);
		p = p->next;
	}
	return true;
}
