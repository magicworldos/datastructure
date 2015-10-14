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
bool init_list(s_list *list)
{
	if (list == null)
	{
		return false;
	}
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

	//从头节点开始释放
	s_node *p = list->header;
	while (p != null)
	{
		s_node *t = p;
		p = p->next;
		free(t);
	}
	list->header = null;

	return true;
}

//插入一个新元素
bool list_insert(s_list *list, int e, int c)
{
	if (list == null)
	{
		return false;
	}

	//申请新节点内存
	s_node *p_new = (s_node *) malloc(sizeof(s_node));
	p_new->exp = e;
	p_new->coe = c;
	p_new->next = null;

	//如果头节点为空
	if (list->header == null)
	{
		//设置头节点为插入元素
		list->header = p_new;
		return true;
	}
	else
	{
		s_node *p = list->header;
		while (p->next != null)
		{
			p = p->next;
		}
		p->next = p_new;
	}

	return false;
}

//多项式相加
bool list_add(s_list *list_one, s_list *list_two, s_list *list_out)
{
	if (list_one == null || list_two == null || list_out == null)
	{
		return false;
	}

	//取得等等相加的多项式头节点
	s_node *p1 = list_one->header;
	s_node *p2 = list_two->header;

	//循环相加
	while (!(p1 == null && p2 == null))
	{
		//如果p1为空，则处理剩余的p2项
		if (p1 == null && p2 != null)
		{
			list_insert(list_out, p2->exp, p2->coe);
			p2 = p2->next;
		}
		//如果p2为空，则处理剩余的p1项
		else if (p1 != null && p2 == null)
		{
			list_insert(list_out, p1->exp, p1->coe);
			p1 = p1->next;
		}
		//如果p1的指数小，则处理p1
		else if (p1->exp < p2->exp)
		{
			list_insert(list_out, p1->exp, p1->coe);
			p1 = p1->next;
		}
		//如果p2的指数小，则处理p2
		else if (p1->exp > p2->exp)
		{
			list_insert(list_out, p2->exp, p2->coe);
			p2 = p2->next;
		}
		//如果指数相同
		else if (p1->exp == p2->exp)
		{
			//如果计算系数结果不为0，则处理
			if (p1->coe + p2->coe != 0)
			{
				list_insert(list_out, p1->exp, p1->coe + p2->coe);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return true;
}

//显示多项式
bool list_display(s_list *list)
{
	if (list == null || list->header == null)
	{
		return false;
	}

	//顺序访问每一个元素
	s_node *p = list->header;
	while (p != null)
	{
		if (p == list->header)
		{
			printf("%d", p->coe);
		}
		else
		{
			printf("%+d", p->coe);
		}
		if (p->exp != 0)
		{
			if (p->exp == 1)
			{
				printf("x", p->exp);
			}
			else
			{
				printf("x^%d", p->exp);
			}
		}
		p = p->next;
	}
	return true;
}
