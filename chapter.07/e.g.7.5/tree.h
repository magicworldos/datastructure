/*
 * tree.h
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#ifndef TREE_H_
#define TREE_H_

#include "typedef.h"

typedef union
{
	int key;
	struct s_node *child;
} s_point_key;

typedef struct s_pk_node
{
	struct s_node *header;
	s_point_key *pk;
	struct s_pk_node *pre;
	struct s_pk_node *next;
} s_pk_node;

//二叉树节点
typedef struct s_node
{
	s_pk_node *parent;
	int key_num;
	s_pk_node *pk_node;
} s_node;

//二叉树数据结构
typedef struct s_tree
{
	//根节点
	s_node *root;
	//阶
	int m;
} s_tree;

//初始化树
bool tree_init(s_tree *tree, int m);

//销毁树
bool tree_destroy(s_tree *tree);

s_node* tree_search(s_node *node, int key);

bool tree_insert(s_tree *tree, int val);

bool tree_insert_node(s_tree *tree, s_pk_node *pk_node, s_node *node, int key);

void tree_insert_pk_node(s_pk_node *pk_node, int type, int key);

void tree_split_node(s_tree *tree, s_node *node);

#endif /* TREE_H_ */
