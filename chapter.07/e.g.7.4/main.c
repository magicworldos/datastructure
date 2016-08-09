#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char **args)
{

	//初始化树
	s_tree tree;
	tree_init(&tree);

//	tree_insert(&tree, 1);
//	tree_insert(&tree, 3);
//	tree_insert(&tree, 4);
//	tree_insert(&tree, 6);
//	tree_insert(&tree, 7);
//	tree_insert(&tree, 2);
//	tree_insert(&tree, 9);
//	tree_insert(&tree, 8);
//	tree_insert(&tree, 0);
//	tree_insert(&tree, 5);
//
//	tree_delete(&tree, 3);
//	tree_delete(&tree, 5);
//	tree_delete(&tree, 4);

	for (int i = 0; i < 100; i++)
	{
		tree_insert(&tree, i);
	}

	for (int i = 0; i < 90; i++)
	{
		tree_delete(&tree, i);
	}

	//中序遍历
	tree_inorder_visit(&tree, tree.root);

	//销毁树
	tree_destroy(&tree);

	return 0;
}

