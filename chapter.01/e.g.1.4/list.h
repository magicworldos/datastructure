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
	void *data;
	struct s_node *pre;
	struct s_node *next;
} s_node;

//表数据结构
typedef struct
{
	//元素大小
	int ele_size;
	//链表大小
	int length;
	//头节点
	s_node *header;
	//用于释放节点数据的回调函数
	void (*free_data)();
	//用于访问节点数据内容的回调函数
	void (*visit_data)(void *data);
} s_list;

//构建一个顺序线性表
bool init_list(s_list *list, int ele_size, void (*free_data)(), void (*visit_data)());

//销毁表
bool destroy_list(s_list *list);

//清空表中所有元素
bool clear_list(s_list *list);

//取得表中现有元素个数
int list_length(s_list *list);

//取得在第i个位置元素的数据内容
bool get_element(s_list *list, int i, void *e);

//在第i个位置前插入一个新元素
bool list_insert(s_list *list, int i, void *e);

//删除第i个元素
bool list_delete(s_list *list, int i);

//对每个元素执行visit操作
bool list_visit(s_list *list);

#endif
