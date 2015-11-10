#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//删除整数函数
void free_int(int *i)
{
	if (i != null)
	{
		free(i);
	}
}

//访问整数函数
void visit_int(int *i)
{
	if (i != null)
	{
		printf("%d", *i);
	}
}

int main(int argc, char **args)
{
	int *t0 = (int *) malloc(sizeof(int));
	int *t1 = (int *) malloc(sizeof(int));
	int *t2 = (int *) malloc(sizeof(int));

	*t0 = 0;
	*t1 = 1;
	*t2 = 2;

	//初始化树
	s_tree tree;
	tree_init(&tree, &visit_int, &free_int);

	s_node *n0 = (s_node *) malloc(sizeof(s_node));
	s_node *n1 = (s_node *) malloc(sizeof(s_node));
	s_node *n2 = (s_node *) malloc(sizeof(s_node));

	n0->parent = null;
	n0->left_child = null;
	n0->right_child = null;
	n0->data = t0;

	n1->parent = null;
	n1->left_child = null;
	n1->right_child = null;
	n1->data = t1;

	n2->parent = null;
	n2->left_child = null;
	n2->right_child = null;
	n2->data = t2;

	//插入根节点
	s_node *node = tree.root;
	tree_insert(&tree, node, 0, n0);
	//插入根节点的左孩子
	node = tree.root;
	tree_insert(&tree, node, 0, n1);
	//插入根节点的右孩子
	node = tree.root;
	tree_insert(&tree, node, 1, n2);

	//得到根节点
	s_node *p = tree_root(&tree);
	visit_int(p->data);
	printf("\n");

	//得到父节点
	p = tree_parent(&tree, t1);
	visit_int(p->data);
	printf("\n");

	//得到父节点
	p = tree_parent(&tree, t2);
	visit_int(p->data);
	printf("\n");

	//得到左孩子
	p = tree_left_child(&tree, t0);
	visit_int(p->data);
	printf("\n");

	//得到右孩子
	p = tree_right_child(&tree, t0);
	visit_int(p->data);
	printf("\n");

	//得到左兄弟
	p = tree_left_brother(&tree, t2);
	visit_int(p->data);
	printf("\n");

	//得到右兄弟
	p = tree_right_brother(&tree, t1);
	visit_int(p->data);
	printf("\n");

	//删除根节点的左孩子
	tree_delete(&tree, tree.root, 0);
	p = tree_left_child(&tree, t0);
	if (p == null)
	{
		printf("Left child of the root node is null.\n");
	}

	//删除根节点的右孩子
	tree_delete(&tree, tree.root, 1);
	p = tree_right_child(&tree, t1);
	if (p == null)
	{
		printf("Right child of the root node is null.\n");
	}

	//销毁树
	tree_destroy(&tree);

	return 0;
}

