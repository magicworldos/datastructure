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

#define INIT_SIZE	(0xff)

typedef struct s_hashtable
{
	s_list *list;
	int list_size;
	int max_size;
} s_hashtable;

bool hashtable_init(s_hashtable *ht, void (*free_data)());

bool hashtable_destory(s_hashtable *ht);

bool hashtable_push(s_hashtable *ht, int key, void *value);

void* hashtable_get(s_hashtable *ht, int key);

bool hashtable_remove(s_hashtable *ht, int key);

#endif /* HASHTABLE_H_ */
