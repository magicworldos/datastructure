#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char **args)
{

	//初始化树
	s_tree tree;
	tree_init(&tree);

	tree_insert(&tree, 5);
	tree_insert(&tree, 3);
	tree_insert(&tree, 4);
	tree_insert(&tree, 6);
	tree_insert(&tree, 7);
	tree_insert(&tree, 2);
	tree_insert(&tree, 9);
	tree_insert(&tree, 8);
	tree_insert(&tree, 0);
	tree_insert(&tree, 1);

	//中序遍历
	tree_inorder_visit(&tree, tree.root);

	//销毁树
	tree_destroy(&tree);

	return 0;
}

