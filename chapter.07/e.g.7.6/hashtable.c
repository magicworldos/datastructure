/*
 * hashtable.c
 *
 *  Created on: Feb 23, 2016
 *      Author: lidq
 */

#include "hashtable.h"

bool hashtable_init(s_hashtable *ht, void (*free_data)())
{
	if (ht == null)
	{
		return false;
	}

	ht->list_size = 0;
	ht->max_size = INIT_SIZE;
	ht->list = (s_list *) malloc(sizeof(s_list) * ht->max_size);
	for (int i = 0; i < ht->max_size; i++)
	{
		init_list(&ht->list[i], free_data);
	}

	return true;
}

//销毁哈希表
bool hashtable_destory(s_hashtable *ht)
{
	for (int i = 0; i < ht->max_size; i++)
	{
		//销毁线性表
		destroy_list(&ht->list[i]);
	}

	free(ht->list);

	return true;
}

//插入数据到哈希表
bool hashtable_push(s_hashtable *ht, int key, void *value)
{
	//计算哈希值
	char h_key = 0xff & key;
	h_key += 0xff & (key >> 8);
	h_key += 0xff & (key >> 16);
	h_key += 0xff & (key >> 24);

	//插入数据
	return list_insert(&ht->list[h_key], key, value);
}

//移除一个数据
bool hashtable_remove(s_hashtable *ht, int key)
{
	//计算哈希值
	char h_key = 0xff & key;
	h_key += 0xff & (key >> 8);
	h_key += 0xff & (key >> 16);
	h_key += 0xff & (key >> 24);

	//移除数据
	return list_delete(&ht->list[h_key], key);
}

//取得数据
void* hashtable_get(s_hashtable *ht, int key)
{
	//计算哈希值
	char h_key = 0xff & key;
	h_key += 0xff & (key >> 8);
	h_key += 0xff & (key >> 16);
	h_key += 0xff & (key >> 24);

	//取得数据
	return list_get(&ht->list[h_key], key);
}
