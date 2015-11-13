/*
 * tree.c
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#include <stdlib.h>
#include "tree.h"

//初始化树
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

//销毁树
bool tree_destroy(s_tree *tree)
{
	if (tree == null)
	{
		return false;
	}

	//清空树
	tree_clear(tree, tree->root);

	//根节点置空
	tree->root = null;

	return true;
}

//清空树
void tree_clear(s_tree *tree, s_node *node)
{
	if (node == null)
	{
		return;
	}

	//递归清空左子树
	tree_clear(tree, node->left_child);
	node->left_child = null;
	//递归清空右子树
	tree_clear(tree, node->right_sibling);
	node->right_sibling = null;

	//如果数据项不为空
	if (node->data != null)
	{
		//释放数据项内存
		tree->free_node(node->data);
	}

	if (node == tree->root)
	{
		tree->root = null;
	}

	//释放当前节点内存
	free(node);
}

//将node_ins插入node的左或右节点，原节点做为node_ins的右节点
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

	//如果是一棵空树
	if (tree->root == null)
	{
		//将节点做为树的根节点
		tree->root = node_ins;
		node_ins->parent = null;
		return true;
	}

	//被插入节点的右子树必须为空
	if (node_ins->right_sibling != null)
	{
		return false;
	}

	//如果插入目标节点的左节点
	if (leftright == 0)
	{
		//插入左节点
		s_node *p_temp = node->left_child;
		node->left_child = node_ins;
		node_ins->parent = node;
		//将原左子树挂接到新节点的右子树上
		node_ins->right_sibling = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}
	//如果插入目标节点的右节点
	else if (leftright == 1)
	{
		//插入右节点
		s_node *p_temp = node->right_sibling;
		node->right_sibling = node_ins;
		node_ins->parent = node;
		//将原右子树挂接到新节点的右子树上
		node_ins->right_sibling = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}

	return true;
}

//初始化节点
bool tree_init_node(s_node *node, void *data)
{
	if (node == null)
	{
		return true;
	}

	node->parent = null;
	node->left_child = null;
	node->right_sibling = null;
	node->data = data;

	return true;
}

//前序遍历
void tree_preamble_visit(s_tree *tree, s_node *node)
{
	if (tree == null)
	{
		return;
	}
	if (tree->root == null)
	{
		return;
	}
	if (node == null)
	{
		return;
	}

	//中
	tree->visit_node(node->data);
	//左
	tree_preamble_visit(tree, node->left_child);
	//右
	tree_preamble_visit(tree, node->right_sibling);
}

//中序遍历
void tree_inorder_visit(s_tree *tree, s_node *node)
{
	if (tree == null)
	{
		return;
	}
	if (tree->root == null)
	{
		return;
	}
	if (node == null)
	{
		return;
	}

	//左
	tree_inorder_visit(tree, node->left_child);
	//中
	tree->visit_node(node->data);
	//右
	tree_inorder_visit(tree, node->right_sibling);
}

//后序遍历
void tree_postorder_visit(s_tree *tree, s_node *node)
{
	if (tree == null)
	{
		return;
	}
	if (tree->root == null)
	{
		return;
	}
	if (node == null)
	{
		return;
	}

	//左
	tree_postorder_visit(tree, node->left_child);
	//右
	tree_postorder_visit(tree, node->right_sibling);
	//中
	tree->visit_node(node->data);
}
