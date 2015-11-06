/*
 * list.c
 *
 *  Created on: Nov 5, 2015
 *      Author: lidq
 */

#include "list.h"
#include <stdio.h>

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

void list_display(s_list *list, char ch)
{
	if (list == null)
	{
		return;
	}

	if (list->tag)
	{
		printf("(");
		list_display(list->child, ch - 1);
		printf(")%c^%d", ch, list->exp);
	}
	else
	{
		printf("%+d%c^%d", list->coe, ch, list->exp);
	}

	if (list->next != null)
	{
		list = list->next;
		printf("+");
		list_display(list, ch);
	}
}
