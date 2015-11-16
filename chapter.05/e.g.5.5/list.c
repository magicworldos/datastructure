/*
 * list.c
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#include <stdlib.h>
#include "list.h"

//按升序插入链表
bool list_insert(s_list *list, int weights, void *data)
{
	if (list == null || data == null)
	{
		return false;
	}

	//申请新节点内存
	s_list *p_new = (s_list *) malloc(sizeof(s_list));
	p_new->weights = weights;
	p_new->data = data;
	p_new->next = null;

	//第一个节点
	if (list->next == null)
	{
		list->next = p_new;
		return true;
	}

	//按顺序插入节点
	s_list *p = list;
	while (p->next != null)
	{
		//只在权重小于下一个节点时插入
		if (p_new->weights <= p->next->weights)
		{
			//插入新节点
			p_new->next = p->next;
			p->next = p_new;

			return true;
		}
		p = p->next;
	}

	p->next = p_new;
	return true;
}

//删除链表中指定元素节点
bool list_delete(s_list *list, void *data)
{
	if (list == null)
	{
		return false;
	}

	s_list *p = list;
	while (p->next != null)
	{
		//找到数据相同的节点
		if (p->next->data == data)
		{
			//删除节点
			s_list *p_del = p->next;
			p->next = p_del->next;
			//释放内存
			free(p_del);

			return true;
		}
		p = p->next;
	}

	return false;
}
