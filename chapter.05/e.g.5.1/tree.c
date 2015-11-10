/*
 * tree.c
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#include <stdlib.h>
#include "tree.h"

bool tree_init(s_tree *tree, void (*visit_node)(), void (*free_node)())
{
	if (tree == null)
	{
		return false;
	}

	tree->root = null;
	tree->visit_node = visit_node;
	tree->free_node = free_node;

	return true;
}

bool tree_destroy(s_tree *tree)
{
	if (tree == null)
	{
		return false;
	}

	tree_clear(tree, tree->root);

	tree->root = null;

	return true;
}

void tree_clear(s_tree *tree, s_node *node)
{
	if (node == null)
	{
		return;
	}

	tree_clear(tree, node->left_child);
	tree_clear(tree, node->right_child);

	if (node->data != null)
	{
		tree->free_node(node->data);
	}

	node->left_child = null;
	node->right_child = null;

	if (node == tree->root)
	{
		tree->root = null;
	}
	free(node);
}

s_node* tree_root(s_tree *tree)
{
	if (tree == null)
	{
		return null;
	}

	return tree->root;
}

bool tree_find_node(s_node *node, s_node **node_f, void *data)
{
	if (node == null)
	{
		return false;
	}

	if (node_f == null)
	{
		return false;
	}

	if (data == null)
	{
		return false;
	}

	if (node->data == data)
	{
		*node_f = node;
		return true;
	}

	if (tree_find_node(node->left_child, node_f, data))
	{
		return true;
	}

	if (tree_find_node(node->right_child, node_f, data))
	{
		return true;
	}

	return false;
}

s_node* tree_parent(s_tree *tree, void *data)
{
	if (tree == null)
	{
		return null;
	}

	if (data == null)
	{
		return null;
	}

	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	return node_find->parent;
}

s_node* tree_left_child(s_tree *tree, void *data)
{
	if (tree == null)
	{
		return null;
	}

	if (data == null)
	{
		return null;
	}

	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	return node_find->left_child;
}

s_node* tree_right_child(s_tree *tree, void *data)
{
	if (tree == null)
	{
		return null;
	}

	if (data == null)
	{
		return null;
	}

	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	return node_find->right_child;
}

s_node* tree_left_brother(s_tree *tree, void *data)
{
	if (tree == null)
	{
		return null;
	}

	if (data == null)
	{
		return null;
	}

	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	if (node_find->parent == null)
	{
		return null;
	}

	if (node_find == node_find->parent->left_child)
	{
		return null;
	}

	return node_find->parent->left_child;
}

s_node* tree_right_brother(s_tree *tree, void *data)
{
	if (tree == null)
	{
		return null;
	}

	if (data == null)
	{
		return null;
	}

	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	if (node_find->parent == null)
	{
		return null;
	}

	if (node_find == node_find->parent->right_child)
	{
		return null;
	}

	return node_find->parent->right_child;
}

bool tree_insert(s_tree *tree, s_node *node, int leftright, s_node *node_ins)
{
	if (tree == null)
	{
		return false;
	}

	if (node_ins == null)
	{
		return false;
	}

	if (tree->root == null)
	{
		tree->root = node_ins;
		node_ins->parent = null;
		return true;
	}

	if (node_ins->right_child != null)
	{
		return false;
	}

	if (leftright == 0)
	{
		s_node *p_temp = node->left_child;
		node->left_child = node_ins;
		node_ins->parent = node;
		node_ins->right_child = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}
	else if (leftright == 1)
	{
		s_node *p_temp = node->right_child;
		node->right_child = node_ins;
		node_ins->parent = node;
		node_ins->right_child = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}

	return true;
}

void tree_delete_node(s_tree *tree, s_node *node)
{
	if (node == null)
	{
		return;
	}

	tree_clear(tree, node->left_child);
	tree_clear(tree, node->right_child);

	if (node->data != null)
	{
		tree->free_node(node->data);
	}

	node->left_child = null;
	node->right_child = null;

	if (node == tree->root)
	{
		tree->root = null;
	}
	free(node);
}

bool tree_delete(s_tree *tree, s_node *node, int leftright)
{
	if (tree == null)
	{
		return false;
	}

	if (node == null)
	{
		return false;
	}

	if (leftright == 0)
	{
		tree_delete_node(tree, node->left_child);
		node->left_child = null;
	}
	else if (leftright == 1)
	{
		tree_delete_node(tree, node->right_child);
		node->right_child = null;
	}

	return true;
}
