#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <avl_tree.h>

int main(int argc, char **args)
{
	//初始化树
	s_avl_tree tree;
	avl_tree_init(&tree);

	avl_tree_put(&tree, 0, NULL);
	avl_tree_put(&tree, 1, NULL);
	avl_tree_put(&tree, 2, NULL);
	avl_tree_put(&tree, 3, NULL);
	avl_tree_put(&tree, 4, NULL);
	avl_tree_put(&tree, 5, NULL);
	avl_tree_put(&tree, 6, NULL);
	avl_tree_put(&tree, 7, NULL);
	avl_tree_put(&tree, 8, NULL);
	avl_tree_put(&tree, 9, NULL);

	//中序遍历
	avl_tree_inorder_visit(&tree, tree.root);
	//显示树型结构
	avl_tree_inorder_display(&tree, tree.root, 0);

	//销毁树
	avl_tree_destroy(&tree);

	return 0;
}

