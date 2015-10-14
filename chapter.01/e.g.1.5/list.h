/*
 * list.h
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "typedef.h"

//多项式每一项节点
typedef struct s_node
{
	//指数
	int exp;
	//系数
	int coe;
	//下一节点指针
	struct s_node *next;
} s_node;

//表数据结构
typedef struct
{
	//头节点
	s_node *header;
} s_list;

//构建一个顺序线性表
bool init_list(s_list *list);

//销毁表
bool destroy_list(s_list *list);

//插入一个新元素
bool list_insert(s_list *list, int e, int c);

//多项式相加
bool list_add(s_list *list_one, s_list *list_two, s_list *list_out);

//显示多项式
bool list_display(s_list *list);

#endif
