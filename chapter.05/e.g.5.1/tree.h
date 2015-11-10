/*
 * tree.h
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#ifndef TREE_H_
#define TREE_H_

#include "typedef.h"

typedef struct s_node
{
	void *data;
	struct s_node *parent;
	struct s_node *left_child;
	struct s_node *right_child;

} s_node;

typedef struct s_tree
{
	s_node *root;
	void (*visit_node)();
	void (*free_node)();
} s_tree;


bool tree_init(s_tree *tree, void (*visit_node)(), void (*free_node)());

bool tree_destroy(s_tree *tree);

void tree_clear(s_tree *tree, s_node *node);

s_node* tree_root(s_tree *tree);

bool tree_find_node(s_node *node, s_node **node_f, void *data);

s_node* tree_parent(s_tree *tree, void *data);

s_node* tree_left_child(s_tree *tree, void *data);

s_node* tree_right_child(s_tree *tree, void *data);

s_node* tree_left_brother(s_tree *tree, void *data);

s_node* tree_right_brother(s_tree *tree, void *data);

bool tree_insert(s_tree *tree, s_node *node, int leftright, s_node *node_ins);

void tree_delete_node(s_tree *tree, s_node *node);

bool tree_delete(s_tree *tree, s_node *node, int leftright);

#endif /* TREE_H_ */
