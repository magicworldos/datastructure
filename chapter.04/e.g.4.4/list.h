/*
 * list.h
 *
 *  Created on: Nov 5, 2015
 *      Author: lidq
 */

#ifndef LIST_H_
#define LIST_H_

#include "typedef.h"

typedef struct s_list
{
	//0表示原子，1表示子表
	int tag;
	//指数
	int exp;
	//共用体
	union
	{
		//系数
		int coe;
		//子表
		struct s_list* child;
	};

	//下一个结点
	struct s_list* next;

} s_list;

//追加节点
bool list_append(s_list *list, s_list* nlist);

//初始化表节点
bool list_init(s_list *list);

//插入原子节点或子表
bool list_insert_value(s_list *list, int tag, int exp, int val);

//显示多项式
void list_display(s_list *list, char ch);

//求广义表深度
void list_depth(s_list *list, int *depth);

//复制广义表
void list_copy(s_list *target, s_list *source);

#endif /* LIST_H_ */
