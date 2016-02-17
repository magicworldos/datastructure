#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char **args)
{

	//初始化3阶B-树
	s_tree tree;
	tree_init(&tree, 3);

	tree_insert(&tree, 1);
	tree_insert(&tree, 3);
	tree_insert(&tree, 2);
	tree_insert(&tree, 4);
	tree_insert(&tree, 6);
	tree_insert(&tree, 7);
	tree_insert(&tree, 9);
	tree_insert(&tree, 8);
	tree_insert(&tree, 0);
	tree_insert(&tree, 5);

	//中序遍历
	//tree_inorder_visit(&tree, tree.root);

	for (int i = 0; i < 10; ++i)
	{
		s_node *p = tree_search(tree.root, i);
		if (p == null)
		{
			printf("NG %d.\n", i);
		}
		else
		{
			printf("OK %d.\n", i);
		}
	}
	//销毁树
	tree_destroy(&tree);

	return 0;
}

