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
bool init_list(s_list *list, void (*free_data)())
{
	if (list == null)
	{
		return false;
	}

	list->free_data = free_data;
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
		if (list->free_data != null)
		{
			list->free_data(p->data);
		}
		s_node *t = p;
		p = p->next;
		free(t);
	}
	list->header = null;

	return true;
}

//插入一个新元素
bool list_insert(s_list *list, int key, void *value)
{
	if (list == null)
	{
		return false;
	}

	s_node *p = list->header;
	if (p == null)
	{
		//申请新节点内存
		s_node *p_new = (s_node *) malloc(sizeof(s_node));
		p_new->key = key;
		p_new->data = value;
		p_new->next = null;
		list->header = p_new;
		return true;
	}

	//如果遇到key相同的节点，则替换值
	while (p->next != null)
	{
		if (p->key == key)
		{
			if (list->free_data != null)
			{
				list->free_data(p->data);
			}
			p->data = value;
			return true;
		}
		p = p->next;
	}

	//替换值
	if (p->key == key)
	{
		if (list->free_data != null)
		{
			list->free_data(p->data);
		}
		p->data = value;
		return true;
	}

	//申请新节点内存
	s_node *p_new = (s_node *) malloc(sizeof(s_node));
	p_new->key = key;
	p_new->data = value;
	p_new->next = null;
	p->next = p_new;

	return false;
}

//删除元素
bool list_delete(s_list *list, int key)
{
	if (list == null || list->header == null)
	{
		return false;
	}

	//删除头节点
	s_node *p = list->header;
	if (p->key == key)
	{
		list->header = p->next;
		if (list->free_data != null)
		{
			list->free_data(p->data);
		}
		free(p);
		return true;
	}

	//查找并删除节点
	while (p->next != null)
	{
		if (p->next->key == key)
		{
			s_node *p_del = p->next;
			p->next = p_del->next;
			if (list->free_data != null)
			{
				list->free_data(p_del->data);
			}
			free(p_del);
			return true;
		}
		p = p->next;
	}

	return false;
}

//根据关键字取得数据
void* list_get(s_list *list, int key)
{
	if (list == null)
	{
		return false;
	}

	//查找key的值
	s_node *p = list->header;
	while (p != null)
	{
		if (p->key == key)
		{
			return p->data;
		}
		p = p->next;
	}

	return null;
}
