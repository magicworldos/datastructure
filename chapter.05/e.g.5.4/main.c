#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		printf("%d ", *i);
	}
}

//多叉树的二叉树表示法
void sample_A()
{
	int *t0 = (int *) malloc(sizeof(int));
	int *t1 = (int *) malloc(sizeof(int));
	int *t2 = (int *) malloc(sizeof(int));
	int *t3 = (int *) malloc(sizeof(int));
	int *t4 = (int *) malloc(sizeof(int));
	int *t5 = (int *) malloc(sizeof(int));
	int *t6 = (int *) malloc(sizeof(int));
	int *t7 = (int *) malloc(sizeof(int));
	int *t8 = (int *) malloc(sizeof(int));

	*t0 = 0;
	*t1 = 1;
	*t2 = 2;
	*t3 = 3;
	*t4 = 4;
	*t5 = 5;
	*t6 = 6;
	*t7 = 7;
	*t8 = 8;

	//初始化树
	s_tree tree;
	tree_init(&tree, &visit_int, &free_int);

	s_node *n0 = (s_node *) malloc(sizeof(s_node));
	s_node *n1 = (s_node *) malloc(sizeof(s_node));
	s_node *n2 = (s_node *) malloc(sizeof(s_node));
	s_node *n3 = (s_node *) malloc(sizeof(s_node));
	s_node *n4 = (s_node *) malloc(sizeof(s_node));
	s_node *n5 = (s_node *) malloc(sizeof(s_node));
	s_node *n6 = (s_node *) malloc(sizeof(s_node));
	s_node *n7 = (s_node *) malloc(sizeof(s_node));
	s_node *n8 = (s_node *) malloc(sizeof(s_node));

	tree_init_node(n0, t0);
	tree_init_node(n1, t1);
	tree_init_node(n2, t2);
	tree_init_node(n3, t3);
	tree_init_node(n4, t4);
	tree_init_node(n5, t5);
	tree_init_node(n6, t6);
	tree_init_node(n7, t7);
	tree_init_node(n8, t8);

	//插入根节点
	tree_insert(&tree, null, 0, n0);
	tree_insert(&tree, n0, 0, n1);
	tree_insert(&tree, n1, 1, n2);
	tree_insert(&tree, n2, 0, n4);
	tree_insert(&tree, n2, 1, n3);
	tree_insert(&tree, n4, 1, n5);
	tree_insert(&tree, n3, 0, n6);
	tree_insert(&tree, n6, 1, n7);
	tree_insert(&tree, n7, 1, n8);

	//前序遍历
	tree_preamble_visit(&tree, tree.root);
	printf("\n");
	//中序遍历
	tree_inorder_visit(&tree, tree.root);
	printf("\n");
	//后序遍历
	tree_postorder_visit(&tree, tree.root);
	printf("\n");

	//销毁树
	tree_destroy(&tree);
}

//森林的二叉树表示法
void sample_B()
{
	int *t0 = (int *) malloc(sizeof(int));
	int *t1 = (int *) malloc(sizeof(int));
	int *t2 = (int *) malloc(sizeof(int));
	int *t3 = (int *) malloc(sizeof(int));
	int *t4 = (int *) malloc(sizeof(int));
	int *t5 = (int *) malloc(sizeof(int));
	int *t6 = (int *) malloc(sizeof(int));
	int *t7 = (int *) malloc(sizeof(int));
	int *t8 = (int *) malloc(sizeof(int));

	*t0 = 0;
	*t1 = 1;
	*t2 = 2;
	*t3 = 3;
	*t4 = 4;
	*t5 = 5;
	*t6 = 6;
	*t7 = 7;
	*t8 = 8;

	//初始化树
	s_tree tree;
	tree_init(&tree, &visit_int, &free_int);

	s_node *n0 = (s_node *) malloc(sizeof(s_node));
	s_node *n1 = (s_node *) malloc(sizeof(s_node));
	s_node *n2 = (s_node *) malloc(sizeof(s_node));
	s_node *n3 = (s_node *) malloc(sizeof(s_node));
	s_node *n4 = (s_node *) malloc(sizeof(s_node));
	s_node *n5 = (s_node *) malloc(sizeof(s_node));
	s_node *n6 = (s_node *) malloc(sizeof(s_node));
	s_node *n7 = (s_node *) malloc(sizeof(s_node));
	s_node *n8 = (s_node *) malloc(sizeof(s_node));

	tree_init_node(n0, t0);
	tree_init_node(n1, t1);
	tree_init_node(n2, t2);
	tree_init_node(n3, t3);
	tree_init_node(n4, t4);
	tree_init_node(n5, t5);
	tree_init_node(n6, t6);
	tree_init_node(n7, t7);
	tree_init_node(n8, t8);

	//插入根节点
	tree_insert(&tree, null, 0, n0);
	tree_insert(&tree, n0, 0, n1);
	tree_insert(&tree, n1, 1, n2);
	tree_insert(&tree, n2, 0, n3);
	tree_insert(&tree, n2, 1, n6);
	tree_insert(&tree, n3, 1, n4);
	tree_insert(&tree, n4, 1, n5);
	tree_insert(&tree, n6, 0, n7);
	tree_insert(&tree, n7, 1, n8);

	//前序遍历
	tree_preamble_visit(&tree, tree.root);
	printf("\n");
	//中序遍历
	tree_inorder_visit(&tree, tree.root);
	printf("\n");
	//后序遍历
	tree_postorder_visit(&tree, tree.root);
	printf("\n");

	//销毁树
	tree_destroy(&tree);
}

int main(int argc, char **args)
{
	sample_A();

	printf("\n");

	sample_B();

	return 0;
}

