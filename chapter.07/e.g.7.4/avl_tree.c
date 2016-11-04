/*
 * avl_tree.c
 *
 *  Created on: Nov 4, 2016
 *      Author: lidq
 */

#include <avl_tree.h>

int avl_tree_init(s_avl_tree *tree)
{
	if (tree == NULL)
	{
		return -1;
	}

	tree->root = NULL;

	return 0;
}

int avl_tree_destroy(s_avl_tree *tree)
{
	if (tree == NULL)
	{
		return -1;
	}

	avl_tree_clear(tree, tree->root);

	tree->root = NULL;

	return 0;
}

void avl_tree_clear(s_avl_tree *tree, s_tree_node *node)
{
	if (node == NULL)
	{
		return;
	}

	avl_tree_clear(tree, node->left_child);
	avl_tree_clear(tree, node->right_child);

	node->left_child = NULL;
	node->right_child = NULL;

	if (node == tree->root)
	{
		tree->root = NULL;
	}

	free(node);
}

int avl_tree_put(s_avl_tree *tree, tkey key, void *value)
{
	if (tree == NULL)
	{
		return -1;
	}

	return avl_tree_insert(tree, NULL, &tree->root, key, value);
}

int avl_tree_remove(s_avl_tree *tree, tkey key)
{
	if (tree == NULL)
	{
		return -1;
	}

	return 0;
}

void* avl_tree_get(s_avl_tree *tree, tkey key)
{
	return NULL;
}

int avl_tree_insert(s_avl_tree *tree, s_tree_node *p_node, s_tree_node **node, tkey key, void *value)
{
	if (*node == NULL)
	{
		s_tree_node *p_new = (s_tree_node *) malloc(sizeof(s_tree_node));
		p_new->key = key;
		p_new->bf = 0;
		p_new->height = 0;
		p_new->left_child = NULL;
		p_new->right_child = NULL;
		*node = p_new;

		if (p_node != NULL && key < p_node->key)
		{
			p_node->left_child = p_new;
			return 0;
		}
		if (p_node != NULL && key > p_node->key)
		{
			p_node->right_child = p_new;
			return 0;
		}

		return 0;
	}

	if (key == (*node)->key)
	{
		printf("Find the node, the value is %d.\n", key);
		return -1;
	}
	else if (key < (*node)->key)
	{
		avl_tree_insert(tree, *node, &(*node)->left_child, key, value);
		(*node)->height = avl_tree_height(*node);
		(*node)->bf = avl_tree_bf(*node);
		if (abs((*node)->bf) > 1)
		{
			if ((*node)->left_child->bf == 1)
			{
				avl_tree_single_right(tree, node);
			}
			else if ((*node)->left_child->bf == -1)
			{
				avl_tree_left_right(tree, node);
			}
		}
	}
	else
	{
		avl_tree_insert(tree, *node, &(*node)->right_child, key, value);
		(*node)->height = avl_tree_height(*node);
		(*node)->bf = avl_tree_bf(*node);
		if (abs((*node)->bf) > 1)
		{
			if ((*node)->right_child->bf == -1)
			{
				avl_tree_single_left(tree, node);
			}
			else if ((*node)->right_child->bf == 1)
			{
				avl_tree_right_left(tree, node);
			}
		}
	}

	return 0;
}

int avl_tree_height(s_tree_node *node)
{
	if (node == NULL)
	{
		return -1;
	}

	int height_left = avl_tree_height(node->left_child);
	int height_right = avl_tree_height(node->right_child);
	return height_left > height_right ? height_left + 1 : height_right + 1;
}

int avl_tree_bf(s_tree_node *node)
{
	if (node == NULL)
	{
		return 0;
	}

	if (node->left_child == NULL && node->right_child == NULL)
	{
		return 0;
	}

	if (node->left_child != NULL && node->right_child == NULL)
	{
		return node->height;
	}

	if (node->left_child == NULL && node->right_child != NULL)
	{
		return -(node->height);
	}

	return node->left_child->height - node->right_child->height;
}

void avl_tree_single_right(s_avl_tree *tree, s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->left_child;
	s_tree_node **pC = &(*pB)->right_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	*pB = nC;
	*pC = nA;
	*pA = nB;

	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
}

void avl_tree_single_left(s_avl_tree *tree, s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->right_child;
	s_tree_node **pC = &(*pB)->left_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	*pB = nC;
	*pC = nA;
	*pA = nB;

	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
}

void avl_tree_left_right(s_avl_tree *tree, s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->left_child;
	s_tree_node **pC = &(*pB)->right_child;
	s_tree_node **pD = &(*pC)->left_child;
	s_tree_node **pE = &(*pC)->right_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	*pC = nC->left_child;
	*pB = nC->right_child;
	*pD = nB;
	*pE = nA;
	*pA = nC;

	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nC->height = avl_tree_height(nC);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
	nC->bf = avl_tree_bf(nC);
}

void avl_tree_right_left(s_avl_tree *tree, s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->right_child;
	s_tree_node **pC = &(*pB)->left_child;
	s_tree_node **pD = &(*pC)->left_child;
	s_tree_node **pE = &(*pC)->right_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	*pB = nC->left_child;
	*pC = nC->right_child;
	*pD = nA;
	*pE = nB;
	*pA = nC;

	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nC->height = avl_tree_height(nC);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
	nC->bf = avl_tree_bf(nC);
}

void avl_tree_inorder_visit(s_avl_tree *tree, s_tree_node *node)
{
	if (tree == null)
	{
		return;
	}

	if (tree->root == null)
	{
		return;
	}

	if (node == null)
	{
		return;
	}

	avl_tree_inorder_visit(tree, node->left_child);
	printf("key: %d, height: %d, bf: %d.\n", node->key, node->height, node->bf);
	avl_tree_inorder_visit(tree, node->right_child);
}

void avl_tree_inorder_display(s_avl_tree *tree, s_tree_node *node, int level)
{
	if (tree == null)
	{
		return;
	}

	if (tree->root == null)
	{
		return;
	}

	if (node == null)
	{
		return;
	}

	for (int i = 0; i < level; i++)
	{
		printf("\t");
	}
	printf("%d\n", node->key, node->height, node->bf);

	avl_tree_inorder_display(tree, node->left_child, level + 1);
	avl_tree_inorder_display(tree, node->right_child, level + 1);
}

int abs(int val)
{
	if (val < 0)
	{
		return -val;
	}

	return val;
}
