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
bool tree_insert(s_tree *tree, int val)
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
		p_new->height = 0;
		p_new->bf = 0;
		p_new->parent = null;
		p_new->left_child = null;
		p_new->right_child = null;
		tree->root = p_new;
		return true;
	}
	else
	{
		//递归
		return tree_insert_node(null, 0, tree->root, val);
	}
}

//递归
int tree_insert_node(s_node *p_node, int type_lr, s_node *node, int val)
{
	int ret_height = 0;

	if (node == null)
	{
		s_node *p_new = (s_node *) malloc(sizeof(s_node));
		p_new->weight = val;
		p_new->height = 0;
		p_new->bf = 0;
		p_new->parent = p_node;
		p_new->left_child = null;
		p_new->right_child = null;

		if (p_node != null)
		{
			//left
			if (type_lr == 0)
			{
				p_node->left_child = p_new;
				if (p_node->right_child == null)
				{
					ret_height = 1;
				}
			}
			//right
			else
			{
				p_node->right_child = p_new;
				if (p_node->left_child == null)
				{
					ret_height = 1;
				}
			}
		}
		return ret_height;
	}

	//找到节点
	if (val == node->weight)
	{
		printf("Find the node, the value is 3.\n");
		return true;
	}
	//如果小于当前节点，则在其左子树上处理
	else if (val < node->weight)
	{
		ret_height = tree_insert_node(node, 0, node->left_child, val);
		if (ret_height != 0)
		{
			if (node->height < ret_height)
			{
				node->height = ret_height;
			}
		}
		node->bf = tree_bf(node);
	}
	//如果大于当前节点，则在其左子树上处理
	else
	{
		ret_height = tree_insert_node(node, 1, node->right_child, val);
		if (ret_height != 0)
		{
			if (node->height < ret_height)
			{
				node->height = ret_height;
			}
		}
		node->bf = tree_bf(node);
	}
	ret_height++;
	return ret_height;
}

//计算平衡因子
int tree_bf(s_node *node)
{
	if (node == null)
	{
		return 0;
	}

	if (node->left_child == null && node->right_child == null)
	{
		return 0;
	}
	else if (node->left_child != null && node->right_child == null)
	{
		return node->height;
	}
	else if (node->left_child == null && node->right_child != null)
	{
		return -(node->height);
	}
	else
	{
		return node->left_child->height - node->right_child->height;
	}
}

//void tree_single_left(s_tree *tree, s_node *node)
//{
//	s_node *root = node->parent;
//
//	s_node *A = node;
//	s_node *B = A->left_child;
//
//	s_node *temp = B->right_child;
//	B->right_child = A;
//	A->left_child = temp;
//	A->parent = B;
//	if (A->left_child != null)
//	{
//		A->left_child->parent = A;
//	}
//
//	B->height--;
//	A->height++;
//
//	B->left_child->height--;
//	if (A->right_child != null)
//	{
//		A->right_child++;
//	}
//
//	if (root == null)
//	{
//		tree->root = B;
//	}
//}
//
//void tree_single_right(s_tree *tree, s_node *node)
//{
//	s_node *root = node->parent;
//
//	s_node *A = node;
//	s_node *B = A->right_child;
//
//	s_node *temp = B->left_child;
//	B->left_child = A;
//	A->right_child = temp;
//	A->parent = B;
//	if (A->right_child != null)
//	{
//		A->right_child->parent = A;
//	}
//
//	B->height--;
//	A->height++;
//
//	B->right_child->height--;
//	if (A->left_child != null)
//	{
//		A->left_child++;
//	}
//
//	if (root == null)
//	{
//		tree->root = B;
//	}
//}
//
//void tree_left_right(s_tree *tree, s_node *node)
//{
//	s_node *root = node->parent;
//
//	s_node *A = node;
//	s_node *B = A->left_child;
//	s_node *C = B->right_child;
//	s_node *A_R = A->right_child;
//	s_node *B_L = B->left_child;
//	s_node *C_L = C->left_child;
//	s_node *C_R = C->right_child;
//
//	C->left_child = B;
//	C->right_child = A;
//	B->parent = C;
//	A->parent = C;
//
//	B->left_child = B_L;
//	B->right_child = C_L;
//	B_L->parent = B;
//	C_L->parent = B;
//
//	A->left_child = C_R;
//	A->right_child = A_R;
//	C_R->parent = A;
//	A_R->parent = A;
//
//	if (root == null)
//	{
//		tree->root = C;
//	}
//
//	A->height++;
//	C->height -= 2;
//	A_R->height++;
//}
//
//void tree_right_left(s_tree *tree, s_node *node)
//{
//	s_node *root = node->parent;
//
//	s_node *A = node;
//	s_node *B = A->right_child;
//	s_node *C = B->left_child;
//	s_node *A_L = A->left_child;
//	s_node *C_L = C->left_child;
//	s_node *C_R = C->right_child;
//	s_node *B_R = B->right_child;
//
//	C->left_child = A;
//	C->right_child = B;
//	A->parent = C;
//	B->parent = C;
//
//	A->left_child = A_L;
//	A->right_child = C_L;
//	A_L->parent = A;
//	C_L->parent = A;
//
//	B->left_child = C_R;
//	B->right_child = B_R;
//	C_R->parent = B;
//	B_R->parent = B;
//
//	if (root == null)
//	{
//		tree->root = C;
//	}
//
//	A->height++;
//	C->height -= 2;
//	A_L->height++;
//}

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
	printf("Node weight = %d, height = %d, bf = %d.\n", node->weight, node->height, node->bf);
	//右
	tree_inorder_visit(tree, node->right_child);
}
