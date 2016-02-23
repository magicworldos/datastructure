/*
 * hashtable.h
 *
 *  Created on: Feb 23, 2016
 *      Author: lidq
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "list.h"

//哈希表大小
#define INIT_SIZE	(0xff)

//哈希表
typedef struct s_hashtable
{
	//线性表
	s_list *list;
} s_hashtable;

//初始化哈希表
bool hashtable_init(s_hashtable *ht, void (*free_data)());

//销毁哈希表
bool hashtable_destory(s_hashtable *ht);

//插入数据
bool hashtable_push(s_hashtable *ht, int key, void *value);

//取得数据
void* hashtable_get(s_hashtable *ht, int key);

//移除数据
bool hashtable_remove(s_hashtable *ht, int key);

//计算哈希值
char hashtable_hashcode(int key);

#endif /* HASHTABLE_H_ */
