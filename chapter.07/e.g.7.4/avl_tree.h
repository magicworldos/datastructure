/*
 * avl_tree.h
 *
 *  Created on: Nov 4, 2016
 *      Author: lidq
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <typedef.h>

typedef s32 tkey;

typedef struct s_tree_node
{
	void *value;
	tkey key;
	int bf;
	int height;
//	struct s_tree_node *parent;
	struct s_tree_node *left_child;
	struct s_tree_node *right_child;

} s_tree_node;

typedef struct s_avl_tree
{
	s_tree_node *root;
} s_avl_tree;

int avl_tree_init(s_avl_tree *tree);

int avl_tree_destroy(s_avl_tree *tree);

void avl_tree_clear(s_tree_node **node);

int avl_tree_put(s_avl_tree *tree, tkey key, void *value);

int avl_tree_remove(s_avl_tree *tree, tkey key);

void* avl_tree_get(s_avl_tree *tree, tkey key);

int avl_tree_insert(s_tree_node *p_node, s_tree_node **node, tkey key, void *value);

int avl_tree_delete(s_tree_node **node, tkey key);

int avl_tree_delete_node(s_tree_node **node);

void avl_tree_node_swap(s_tree_node *node, s_tree_node *node1);

s_tree_node** avl_tree_find_max_node(s_tree_node **node);

s_tree_node** avl_tree_find_min_node(s_tree_node **node);

void avl_tree_rebalance(s_tree_node **node);

int avl_tree_height(s_tree_node *node);

int avl_tree_bf(s_tree_node *node);

void avl_tree_single_right(s_tree_node **node);

void avl_tree_single_left(s_tree_node **node);

void avl_tree_left_right(s_tree_node **node);

void avl_tree_right_left(s_tree_node **node);

void avl_tree_inorder_visit(s_avl_tree *tree, s_tree_node *node);

void avl_tree_inorder_display(s_avl_tree *tree, s_tree_node *node, int level);

#endif /* AVL_TREE_H_ */
