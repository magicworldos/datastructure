/*
 * list.c
 *
 *  Created on: Nov 5, 2015
 *      Author: lidq
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//追加节点
bool list_append(s_list *list, s_list* nlist)
{
	if (list == null)
	{
		return false;
	}
	if (nlist == null)
	{
		return false;
	}

	while (list->next != null)
	{
		list = list->next;
	}
	list->next = nlist;

	return true;
}

//初始化表节点
bool list_init(s_list *list)
{
	list->tag = 0;
	list->coe = 0;
	list->child = null;
	list->next = null;

	return true;
}

//插入原子节点或子表
bool list_insert_value(s_list *list, int tag, int exp, int val)
{
	if (list == null)
	{
		return false;
	}

	list->tag = tag;
	list->exp = exp;
	list->coe = val;

	return true;
}

//显示多项式
void list_display(s_list *list, char ch)
{
	if (list == null)
	{
		return;
	}

	//如果当前节点是子表
	if (list->tag)
	{
		printf("(");
		//递归显示子表
		list_display(list->child, ch - 1);
		printf(")%c^%d", ch, list->exp);
	}
	//如果当前节点是原子节点
	else
	{
		//显示原子内容
		printf("%+d%c^%d", list->coe, ch, list->exp);
	}

	//如果下一节点不为空
	if (list->next != null)
	{
		printf("+");
		//递归显示下一节点
		list_display(list->next, ch);
	}
}

//求广义表深度
void list_depth(s_list *list, int *depth)
{
	if (list == null)
	{
		return;
	}

	if (depth == null)
	{
		return;
	}

	//如果当前节点是子表
	if (list->tag)
	{
		*depth += 1;
		//递归求子表深度
		list_depth(list->child, depth);
	}

	//如果下一节点不为空
	if (list->next != null)
	{
		//求同级子表最大深度
		int m = 0;
		list_depth(list->next, &m);
		if (*depth < m)
		{
			*depth = m;
		}
	}
}

//复制广义表
void list_copy(s_list *target, s_list *source)
{
	if (source == null)
	{
		return;
	}

	memcpy(target, source, sizeof(s_list));

	//如果当前节点是子表
	if (source->tag)
	{
		//递归复制子表
		s_list *clist = (s_list *) malloc(sizeof(s_list));
		list_copy(clist, source->child);
		target->child = clist;
	}

	//如果下一节点不为空
	if (source->next != null)
	{
		//递归复制同级广义表
		s_list *nlist = (s_list *) malloc(sizeof(s_list));
		list_copy(nlist, source->next);
		target->next = nlist;
	}
}
