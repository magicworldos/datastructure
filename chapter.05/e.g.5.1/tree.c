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
	//递归清空右子树
	tree_clear(tree, node->right_child);

	//如果数据项不为空
	if (node->data != null)
	{
		//释放数据项内存
		tree->free_node(node->data);
	}

	node->left_child = null;
	node->right_child = null;

	if (node == tree->root)
	{
		tree->root = null;
	}

	//释放当前节点内存
	free(node);
}

//取得根节点
s_node* tree_root(s_tree *tree)
{
	if (tree == null)
	{
		return null;
	}

	return tree->root;
}

//找到数据项在树中的节点
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

	//找到同地址数据项，返回当前节点
	if (node->data == data)
	{
		*node_f = node;
		return true;
	}

	//递归查找左子树
	if (tree_find_node(node->left_child, node_f, data))
	{
		return true;
	}
	//递归查找右子树
	if (tree_find_node(node->right_child, node_f, data))
	{
		return true;
	}

	return false;
}

//找到数据项在树中的父节点
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

	//找到数据项所在的节点
	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	//返回父节点
	return node_find->parent;
}

//找到数据项在树中的左孩子
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

	//找到数据项所在的节点
	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	//返回左孩子节点
	return node_find->left_child;
}

//找到数据项在树中的右孩子
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

	//找到数据项所在的节点
	s_node *node_find = null;
	tree_find_node(tree->root, &node_find, data);
	if (node_find == null)
	{
		return null;
	}

	//返回右孩子节点
	return node_find->right_child;
}

//找到数据项在树中的左兄弟
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

	//找到数据项所在的节点
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

	//返回左兄弟
	return node_find->parent->left_child;
}

//找到数据项在树中的右兄弟
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

	//找到数据项所在的节点
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

	//返回右兄弟
	return node_find->parent->right_child;
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
	if (node_ins->right_child != null)
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
		node_ins->right_child = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}
	//如果插入目标节点的右节点
	else if (leftright == 1)
	{
		//插入右节点
		s_node *p_temp = node->right_child;
		node->right_child = node_ins;
		node_ins->parent = node;
		//将原右子树挂接到新节点的右子树上
		node_ins->right_child = p_temp;
		if (p_temp != null)
		{
			p_temp->parent = node_ins;
		}
	}

	return true;
}

//删除节点
void tree_delete_node(s_tree *tree, s_node *node)
{
	if (node == null)
	{
		return;
	}

	//递归删除左子树
	tree_delete_node(tree, node->left_child);
	//递归删除右子树
	tree_delete_node(tree, node->right_child);

	if (node->data != null)
	{
		tree->free_node(node->data);
	}

	//删除左节点
	node->left_child = null;
	//删除右节点
	node->right_child = null;

	//如果是根节点则清空树
	if (node == tree->root)
	{
		tree->root = null;
	}

	free(node);
}

//删除树的节点
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

	//删除左子树
	if (leftright == 0)
	{
		tree_delete_node(tree, node->left_child);
		node->left_child = null;
	}
	//删除右子树
	else if (leftright == 1)
	{
		tree_delete_node(tree, node->right_child);
		node->right_child = null;
	}

	//如果是根节点则清空树
	if (node == tree->root)
	{
		tree->root = null;
	}

	return true;
}
