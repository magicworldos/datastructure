/*
 * tree.c
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//初始化树
bool tree_init(s_tree *tree)
{
	if (tree == null)
	{
		return false;
	}

	tree->root = null;

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
	//递归清空右子树
	tree_clear(tree, node->right_child);

	node->left_child = null;
	node->right_child = null;

	if (node == tree->root)
	{
		tree->root = null;
	}

	//释放当前节点内存
	free(node);
}

//根据val到二叉树中查找
bool tree_search(s_tree *tree, int val)
{
	if (tree == null)
	{
		return false;
	}

	//如果二叉树没有根节点
	if (tree->root == null)
	{
		//创建权值为val的根节点
		s_node *p_new = (s_node *) malloc(sizeof(s_node));
		p_new->weight = val;
		p_new->parent = null;
		p_new->left_child = null;
		p_new->right_child = null;
		tree->root = p_new;
		return true;
	}
	else
	{
		//递归查找
		return tree_find(tree->root, val);
	}
}

//递归查找节点，如果找不到就插入
bool tree_find(s_node *node, int val)
{
	if (node == null)
	{
		return false;
	}

	//找到节点
	if (val == node->weight)
	{
		printf("Find the node, the value is 3.\n");
	}
	//如果小于当前节点，则在其左子树上处理
	else if (val < node->weight)
	{
		//如果左子树为空
		if (node->left_child == null)
		{
			s_node *p_new = (s_node *) malloc(sizeof(s_node));
			p_new->weight = val;
			p_new->parent = node;
			p_new->left_child = null;
			p_new->right_child = null;
			node->left_child = p_new;
			return true;
		}
		//如果当前值大于左子树
		else if (val > node->left_child->weight)
		{
			s_node *p_new = (s_node *) malloc(sizeof(s_node));
			p_new->weight = val;
			p_new->parent = node;
			p_new->left_child = node->left_child;
			p_new->right_child = null;
			p_new->left_child->parent = p_new;
			node->left_child = p_new;
			return true;
		}
		//如果小于左子树
		else
		{
			//递归处理其左子树
			return tree_find(node->left_child, val);
		}
	}
	//如果大于当前节点，则在其左子树上处理
	else
	{
		//如果右子树为空
		if (node->right_child == null)
		{
			s_node *p_new = (s_node *) malloc(sizeof(s_node));
			p_new->weight = val;
			p_new->parent = node;
			p_new->left_child = null;
			p_new->right_child = null;
			node->right_child = p_new;
			return true;
		}
		//如果小于右子树权值
		else if (val < node->right_child->weight)
		{
			s_node *p_new = (s_node *) malloc(sizeof(s_node));
			p_new->weight = val;
			p_new->parent = node;
			p_new->right_child = node->right_child;
			p_new->left_child = null;
			p_new->right_child->parent = p_new;
			node->right_child = p_new;
			return true;
		}
		//如果大于右子树权值
		else
		{
			return tree_find(node->right_child, val);
		}
	}
	return true;
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
	printf("Node weight is %d.\n", node->weight);
	//右
	tree_inorder_visit(tree, node->right_child);
}
