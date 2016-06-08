/*
 * tree.h
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#ifndef TREE_H_
#define TREE_H_

#include "typedef.h"

//二叉树节点
typedef struct s_node
{
	//权重
	int weight;
	//高度
	int height;
	//平衡因子
	int bf;
	//父节点
	struct s_node *parent;
	//左孩子节点
	struct s_node *left_child;
	//右孩子节点
	struct s_node *right_child;
} s_node;

//二叉树数据结构
typedef struct s_tree
{
	//根节点
	s_node *root;
} s_tree;

//初始化树
bool tree_init(s_tree *tree);

//销毁树
bool tree_destroy(s_tree *tree);

//清空树
void tree_clear(s_tree *tree, s_node *node);

//根据val到二叉树中查找
bool tree_insert(s_tree *tree, int val);

//递归
int tree_insert_node(s_tree *tree, s_node *p_node, int type_lr, s_node *node, int val);

//根据val到二叉树中查找
bool tree_delete(s_tree *tree, int val);

//递归
int tree_delete_node(s_tree *tree, s_node *p_node, int type_lr, s_node *node, int val);

int tree_delete_node_leaf(s_tree *tree, s_node *node);

bool tree_delete_bf(s_tree *tree, s_node *node);

void tree_reset_height(s_tree *tree, s_node *node);

s_node* tree_find_max_node(s_node *node);

s_node* tree_find_min_node(s_node *node);

//计算平衡因子
int tree_bf(s_node *node);

//计算节点高度
int tree_height(s_node *node);

//单向左旋
void tree_single_left(s_tree *tree, s_node *node);
//单向右旋

void tree_single_right(s_tree *tree, s_node *node);
//先向左，后向右

void tree_left_right(s_tree *tree, s_node *node);

//先向右，后向左
void tree_right_left(s_tree *tree, s_node *node);

//中序遍历
void tree_inorder_visit(s_tree *tree, s_node *node);

int abs(int val);

#endif /* TREE_H_ */
