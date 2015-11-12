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
	//数据指针
	void *data;
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
	//访问函数指针
	void (*visit_node)();
	//释放内存函数指针
	void (*free_node)();
} s_tree;

//初始化树
bool tree_init(s_tree *tree, void (*visit_node)(), void (*free_node)());

//销毁树
bool tree_destroy(s_tree *tree);

//清空树
void tree_clear(s_tree *tree, s_node *node);

//前序构建二叉树
void tree_create_preamble(s_node *p_node, int left_right, s_node **node, void ***p);

//构建二叉树
bool tree_create(s_tree *tree, int method, void **p);

//取得根节点
s_node* tree_root(s_tree *tree);

//找到数据项在树中的节点
bool tree_find_node(s_node *node, s_node **node_f, void *data);

//找到数据项在树中的父节点
s_node* tree_parent(s_tree *tree, void *data);

//找到数据项在树中的左孩子
s_node* tree_left_child(s_tree *tree, void *data);

//找到数据项在树中的右孩子
s_node* tree_right_child(s_tree *tree, void *data);

//找到数据项在树中的左兄弟
s_node* tree_left_brother(s_tree *tree, void *data);

//找到数据项在树中的右兄弟
s_node* tree_right_brother(s_tree *tree, void *data);

//将node_ins插入node的左或右节点，原节点做为node_ins的右节点
bool tree_insert(s_tree *tree, s_node *node, int leftright, s_node *node_ins);

//删除节点
void tree_delete_node(s_tree *tree, s_node *node);

//删除树的节点
bool tree_delete(s_tree *tree, s_node *node, int leftright);

//初始化节点
bool tree_init_node(s_node *node, void *data);

//前序遍历
void tree_preamble_visit(s_tree *tree, s_node *node);

//中序遍历
void tree_inorder_visit(s_tree *tree, s_node *node);

//后序遍历
void tree_postorder_visit(s_tree *tree, s_node *node);

#endif /* TREE_H_ */
