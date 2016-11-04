#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <avl_tree.h>

int main(int argc, char **args)
{
	srand((int) time(0));
	s_avl_tree tree;
	avl_tree_init(&tree);

	for (int i = 0; i < 100; i++)
	{
		avl_tree_put(&tree, rand() % 100, NULL);
	}

	avl_tree_inorder_visit(&tree, tree.root);
	printf("\n");
	avl_tree_inorder_display(&tree, tree.root, 0);

	avl_tree_destroy(&tree);

	return 0;
}

