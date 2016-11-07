/*
 * avl_tree.h
 *
 *  Created on: Nov 4, 2016
 *      Author: lidq
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <typedef.h>

//关键字变量类型
typedef s32 tkey;

//二叉树节点
typedef struct s_tree_node
{
	//数据值
	void *value;
	//关键字
	tkey key;
	//平衡因子
	int bf;
	//节点高（深度）
	int height;
	//左孩子节点
	struct s_tree_node *left_child;
	//右孩子节点
	struct s_tree_node *right_child;

} s_tree_node;

//平衡二叉树
typedef struct s_avl_tree
{
	//根节点
	s_tree_node *root;
} s_avl_tree;

//初始化平衡二叉树
int avl_tree_init(s_avl_tree *tree);

//销毁平衡二叉树
int avl_tree_destroy(s_avl_tree *tree);

//递归清空子节点
void avl_tree_clear(s_tree_node **node);

//插入新数据
int avl_tree_put(s_avl_tree *tree, tkey key, void *value);

//移除数据
int avl_tree_remove(s_avl_tree *tree, tkey key);

//二叉树查找取得关键字的值
void* avl_tree_get(s_avl_tree *tree, tkey key);

//二叉树查找取得关键字的值
void* avl_tree_get_value(s_tree_node *node, tkey key);

//递归插入数据
int avl_tree_insert(s_tree_node **node, tkey key, void *value);

//删除关键字节点
int avl_tree_delete(s_tree_node **node, tkey key);

int avl_tree_delete_node(s_tree_node **node);

//交换两个节点的关键字和值
void avl_tree_node_swap(s_tree_node *node, s_tree_node *node1);

//找到子树中关键字最大的节点
s_tree_node** avl_tree_find_max_node(s_tree_node **node);

//找到子树中关键字最小的节点
s_tree_node** avl_tree_find_min_node(s_tree_node **node);

//二叉树的平衡处理
void avl_tree_rebalance(s_tree_node **node);

//计算节点的高（深度）
int avl_tree_height(s_tree_node *node);

//计算平衡因子，左子树高减去右子树高
int avl_tree_bf(s_tree_node *node);

//单向右旋
void avl_tree_single_right(s_tree_node **node);

//单向左旋
void avl_tree_single_left(s_tree_node **node);

//先左旋再右旋
void avl_tree_left_right(s_tree_node **node);

//先右旋再左旋
void avl_tree_right_left(s_tree_node **node);

//前序遍历
void avl_tree_inorder_visit(s_avl_tree *tree, s_tree_node *node);

//按树型结构显示平衡二叉树
void avl_tree_inorder_display(s_avl_tree *tree, s_tree_node *node, int level);

#endif /* AVL_TREE_H_ */
