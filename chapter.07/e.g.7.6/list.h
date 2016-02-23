/*
 * list.h
 *
 *  Created on: Oct 9, 2015
 *      Author: lidq
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "typedef.h"

//表节点
typedef struct s_node
{
	//关键字
	int key;
	//数据指针
	void *data;
	//下一个节点
	struct s_node *next;
} s_node;

//表数据结构
typedef struct
{
	//头节点
	s_node *header;
	//用于释放节点数据的回调函数
	void (*free_data)();
} s_list;

//构建性表
bool init_list(s_list *list, void (*free_data)());

//销毁表
bool destroy_list(s_list *list);

//清空表中所有元素
bool clear_list(s_list *list);

//插入一个新元素
bool list_insert(s_list *list, int key, void *value);

//删除元素
bool list_delete(s_list *list, int key);

//根据关键字取得数据
void* list_get(s_list *list, int key);

#endif
