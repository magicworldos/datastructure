#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <avl_tree.h>

int main(int argc, char **args)
{
	int N = 20;
	srand((int) time(0));
	s_avl_tree tree;
	avl_tree_init(&tree);
	int keys[N];
	for (int i = 0; i < N; i++)
	{
		keys[i] = rand() % (N * 100);
		avl_tree_put(&tree, keys[i], NULL);
	}

	printf("--------------------------------------------------\n");
	avl_tree_inorder_display(&tree, tree.root, 0);
	printf("--------------------------------------------------\n");
	avl_tree_inorder_visit(&tree, tree.root);

	for (int i = 0; i < N; i++)
	{
		printf("--------------------------------------------------\n");
		printf("rm %d\n", keys[i]);
		avl_tree_remove(&tree, keys[i]);
		avl_tree_inorder_display(&tree, tree.root, 0);
		printf("--------------------------------------------------\n");
		avl_tree_inorder_visit(&tree, tree.root);
	}

	avl_tree_destroy(&tree);

	printf("Done\n");

	return 0;
}

