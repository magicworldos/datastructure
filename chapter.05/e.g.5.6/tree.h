/*
 * tree.h
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#ifndef TREE_H_
#define TREE_H_

#include "typedef.h"
#include "list.h"

#define MAX_CODE_LEN (20)

//赫夫曼节点
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

//赫夫曼数据结构
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

//初始化节点
bool tree_init_node(s_node *node, void *data);

//生成哈夫曼编码
void tree_huffman_code(s_tree *tree, s_node *node, int *no, char **code);

//找到指定哈夫曼编码的节点数据
bool tree_get_data_by_huffman_code(s_tree *tree, char *code, void **data);

//前序遍历
void tree_preamble_visit(s_tree *tree, s_node *node);

//由一个有序链表构建赫夫曼树
bool tree_create(s_tree *tree, s_list *list);

#endif /* TREE_H_ */
