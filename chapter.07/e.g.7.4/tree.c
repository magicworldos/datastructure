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
		return tree_insert_node(tree, null, 0, tree->root, val);
	}
}

//递归
int tree_insert_node(s_tree *tree, s_node *p_node, int type_lr, s_node *node, int val)
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
		return 0;
	}
	//如果小于当前节点，则在其左子树上处理
	else if (val < node->weight)
	{
		//插入新节点并返回子树高
		ret_height = tree_insert_node(tree, node, 0, node->left_child, val);
		if (ret_height != 0)
		{
			if (node->height < ret_height)
			{
				node->height = ret_height;
			}
		}
		//计算平衡因子
		node->bf = tree_bf(node);

		//如果平衡因子的绝对值大于1，说明出现不平衡现象
		if (abs(node->bf) > 1)
		{
			//新结节为其左子树的左子树
			if (node->left_child->bf == 1)
			{
				//单向右旋
				tree_single_right(tree, node);
			}
			//新结节为其左子树的右子树
			else if (node->left_child->bf == -1)
			{
				//先向左，后向右
				tree_left_right(tree, node);
			}
		}
	}
	//如果大于当前节点，则在其右子树上处理
	else
	{
		//插入新节点并返回子树高
		ret_height = tree_insert_node(tree, node, 1, node->right_child, val);
		if (ret_height != 0)
		{
			if (node->height < ret_height)
			{
				node->height = ret_height;
			}
		}
		//计算平衡因子
		node->bf = tree_bf(node);

		//如果平衡因子的绝对值大于1，说明出现不平衡现象
		if (abs(node->bf) > 1)
		{
			//新结节为其右子树的右子树
			if (node->right_child->bf == -1)
			{
				//单向左旋
				tree_single_left(tree, node);
			}
			//新结节为其右子树的左子树
			else if (node->right_child->bf == 1)
			{
				//先向右，后向左
				tree_right_left(tree, node);
			}
		}
	}
	//高度自增
	ret_height++;
	//返回高度
	return ret_height;
}

//计算平衡因子
int tree_bf(s_node *node)
{
	if (node == null)
	{
		return 0;
	}
	//左右子树均为空，返回0
	if (node->left_child == null && node->right_child == null)
	{
		return 0;
	}
	//左子树不为空，右子树为空，返回左子树的高
	else if (node->left_child != null && node->right_child == null)
	{
		return node->height;
	}
	//右子树不为空，左子树为空，返回右子树的高（取相反数）
	else if (node->left_child == null && node->right_child != null)
	{
		return -(node->height);
	}
	//左子树的高减去右子树的高
	else
	{
		return node->left_child->height - node->right_child->height;
	}
}

//计算高度
int tree_height(s_node *node)
{
	if (node == null)
	{
		return 0;
	}
	//左右子树均为空，返回0
	if (node->left_child == null && node->right_child == null)
	{
		return 0;
	}
	//左子树不为空，右子树为空，返回左子树的高 + 1
	if (node->left_child != null && node->right_child == null)
	{
		return node->left_child->height + 1;
	}
	//右子树不为空，左子树为空，返回右子树的高
	if (node->left_child == null && node->right_child != null)
	{
		return node->right_child->height + 1;
	}
	//如果左子树的高大于右子树的高，返回左子树的高 + 1
	if (node->left_child->height > node->right_child->height)
	{
		return node->left_child->height + 1;
	}

	//如果右子树的高大于左子树的高，返回右子树的高 + 1
	return node->right_child->height + 1;
}

//单向左旋
void tree_single_left(s_tree *tree, s_node *node)
{
	//最小失衡子树的根节点的父节点
	s_node *root = node->parent;

	//定义旋转节点
	s_node *A = node;
	s_node *B = A->right_child;
	s_node *BL = B->left_child;
	s_node *BR = B->right_child;

	//旋转
	B->left_child = A;
	A->right_child = BL;

	A->parent = B;

	if (BL != null)
	{
		BL->parent = A;
	}

	//重新计算高
	A->height = tree_height(A);
	B->height = tree_height(B);
	//重新计算平衡因子
	A->bf = tree_bf(A);
	B->bf = tree_bf(B);

	//旋转后的子树根节点设置
	B->parent = root;
	if (root == null)
	{
		tree->root = B;
	}
	else
	{
		if (A == root->left_child)
		{
			root->left_child = B;
		}
		else if (A == root->right_child)
		{
			root->right_child = B;
		}
	}
}

//单向右旋
void tree_single_right(s_tree *tree, s_node *node)
{
	//最小失衡子树的根节点的父节点
	s_node *root = node->parent;

	//定义旋转节点
	s_node *A = node;
	s_node *B = A->left_child;
	s_node *BR = B->right_child;

	//旋转
	B->right_child = A;
	A->left_child = BR;

	A->parent = B;

	if (BR != null)
	{
		BR->parent = A;
	}

	//重新计算高
	A->height = tree_height(A);
	B->height = tree_height(B);
	//重新计算平衡因子
	A->bf = tree_bf(A);
	B->bf = tree_bf(B);

	//旋转后的子树根节点设置
	B->parent = root;
	if (root == null)
	{
		tree->root = B;
	}
	else
	{
		if (A == root->left_child)
		{
			root->left_child = B;
		}
		else if (A == root->right_child)
		{
			root->right_child = B;
		}
	}
}

//先向左，后向右
void tree_left_right(s_tree *tree, s_node *node)
{
	//最小失衡子树的根节点的父节点
	s_node *root = node->parent;

	//定义旋转节点
	s_node *A = node;
	s_node *B = A->left_child;
	s_node *C = B->right_child;

	s_node *CL = C->left_child;
	s_node *CR = C->right_child;

	//旋转
	C->left_child = B;
	C->right_child = A;
	B->parent = C;
	A->parent = C;

	B->right_child = CL;
	A->left_child = CR;

	if (CL != null)
	{
		CL->parent = B;
	}
	if (CR != null)
	{
		CR->parent = A;
	}

	//重新计算高
	A->height = tree_height(A);
	B->height = tree_height(B);
	C->height = tree_height(C);
	//重新计算平衡因子
	A->bf = tree_bf(A);
	B->bf = tree_bf(B);
	C->bf = tree_bf(C);

	//旋转后的子树根节点设置
	C->parent = root;
	if (root == null)
	{
		tree->root = C;
	}
	else
	{
		if (A == root->left_child)
		{
			root->left_child = C;
		}
		else if (A == root->right_child)
		{
			root->right_child = C;
		}
	}
}

//先向右，后向左
void tree_right_left(s_tree *tree, s_node *node)
{
	//最小失衡子树的根节点的父节点
	s_node *root = node->parent;

	//定义旋转节点
	s_node *A = node;
	s_node *B = A->right_child;
	s_node *C = B->left_child;

	s_node *CL = C->left_child;
	s_node *CR = C->right_child;

	//旋转
	C->left_child = A;
	C->right_child = B;
	A->parent = C;
	B->parent = C;

	A->right_child = CL;
	B->left_child = CR;

	if (CL != null)
	{
		CL->parent = A;
	}
	if (CR != null)
	{
		CR->parent = B;
	}

	//重新计算高
	A->height = tree_height(A);
	B->height = tree_height(B);
	C->height = tree_height(C);
	//重新计算平衡因子
	A->bf = tree_bf(A);
	B->bf = tree_bf(B);
	C->bf = tree_bf(C);

	//旋转后的子树根节点设置
	C->parent = root;
	if (root == null)
	{
		tree->root = C;
	}
	else
	{
		if (A == root->left_child)
		{
			root->left_child = C;
		}
		else if (A == root->right_child)
		{
			root->right_child = C;
		}
	}
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
	printf("Node weight = %d, height = %d, bf = %d.\n", node->weight, node->height, node->bf);
	//右
	tree_inorder_visit(tree, node->right_child);
}

int abs(int val)
{
	if (val < 0)
	{
		return -val;
	}

	return val;
}
