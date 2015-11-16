#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"

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

void sample_A()
{
	s_list *list = (s_list *) malloc(sizeof(s_list));
	list->weights = 0;
	list->data = null;
	list->next = null;

	s_tree tree;
	tree_init(&tree, &visit_int, &free_int);

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

	list_insert(list, 0, n0);
	list_insert(list, 1, n1);
	list_insert(list, 2, n2);
	list_insert(list, 3, n3);
	list_insert(list, 4, n4);
	list_insert(list, 5, n5);
	list_insert(list, 6, n6);
	list_insert(list, 7, n7);
	list_insert(list, 8, n8);

	tree_create(&tree, list);

	//前序遍历
	tree_preamble_visit(&tree, tree.root);
	printf("\n");

	//申请存放哈夫曼编码的字符串的二级指针
	char **code = malloc(sizeof(char *) * 9);
	for (int i = 0; i < 9; i++)
	{
		//申请存放哈夫曼编码的字符串
		code[i] = malloc(sizeof(char) * MAX_CODE_LEN);
	}
	int no = 0;
	//生成哈夫曼编码
	tree_huffman_code(&tree, tree.root, &no, code);

	for (int i = 0; i < 9; i++)
	{
		printf("%s ", code[i]);
		free(code[i]);
	}
	printf("\n");
	free(code);

	//销毁树
	tree_destroy(&tree);

	free(list);
}

void sample_B()
{
	s_list *list = (s_list *) malloc(sizeof(s_list));
	list->weights = 0;
	list->data = null;
	list->next = null;

	s_tree tree;
	tree_init(&tree, &visit_int, &free_int);

	int *t0 = (int *) malloc(sizeof(char));
	int *t1 = (int *) malloc(sizeof(char));
	int *t2 = (int *) malloc(sizeof(char));
	int *t3 = (int *) malloc(sizeof(char));
	int *t4 = (int *) malloc(sizeof(char));
	int *t5 = (int *) malloc(sizeof(char));
	int *t6 = (int *) malloc(sizeof(char));
	int *t7 = (int *) malloc(sizeof(char));

	*t0 = 5;
	*t1 = 29;
	*t2 = 7;
	*t3 = 8;
	*t4 = 14;
	*t5 = 23;
	*t6 = 3;
	*t7 = 11;

	s_node *n0 = (s_node *) malloc(sizeof(s_node));
	s_node *n1 = (s_node *) malloc(sizeof(s_node));
	s_node *n2 = (s_node *) malloc(sizeof(s_node));
	s_node *n3 = (s_node *) malloc(sizeof(s_node));
	s_node *n4 = (s_node *) malloc(sizeof(s_node));
	s_node *n5 = (s_node *) malloc(sizeof(s_node));
	s_node *n6 = (s_node *) malloc(sizeof(s_node));
	s_node *n7 = (s_node *) malloc(sizeof(s_node));

	tree_init_node(n0, t0);
	tree_init_node(n1, t1);
	tree_init_node(n2, t2);
	tree_init_node(n3, t3);
	tree_init_node(n4, t4);
	tree_init_node(n5, t5);
	tree_init_node(n6, t6);
	tree_init_node(n7, t7);

	list_insert(list, 5, n0);
	list_insert(list, 29, n1);
	list_insert(list, 7, n2);
	list_insert(list, 8, n3);
	list_insert(list, 14, n4);
	list_insert(list, 23, n5);
	list_insert(list, 3, n6);
	list_insert(list, 11, n7);

	tree_create(&tree, list);

	//前序遍历
	tree_preamble_visit(&tree, tree.root);
	printf("\n");

	//申请存放哈夫曼编码的字符串的二级指针
	char **code = malloc(sizeof(char *) * 8);
	for (int i = 0; i < 8; i++)
	{
		//申请存放哈夫曼编码的字符串
		code[i] = malloc(sizeof(char) * MAX_CODE_LEN);
	}
	int no = 0;
	//生成哈夫曼编码
	tree_huffman_code(&tree, tree.root, &no, code);

	for (int i = 0; i < 8; i++)
	{
		printf("%s ", code[i]);
		free(code[i]);
	}
	printf("\n");
	free(code);

	//销毁树
	tree_destroy(&tree);

	free(list);
}

int main(int argc, char **args)
{
	sample_A();

	sample_B();

	return 0;
}

