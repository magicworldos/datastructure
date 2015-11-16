/*
 * list.h
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "typedef.h"

//表数据结构
typedef struct s_list
{
	//权重
	int weights;
	//数据项
	void *data;
	//头节点
	struct s_list *next;

} s_list;

//按升序插入链表
bool list_insert(s_list *list, int weights, void *data);

//删除链表中指定元素节点
bool list_delete(s_list *list, void *data);

#endif
