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

	avl_tree_clear(&tree->root);

	return 0;
}

void avl_tree_clear(s_tree_node **node)
{
	if (node == NULL)
	{
		return;
	}

	if (*node == NULL)
	{
		return;
	}

	avl_tree_clear(&(*node)->left_child);
	avl_tree_clear(&(*node)->right_child);

	(*node)->left_child = NULL;
	(*node)->right_child = NULL;

	free(*node);
	*node = NULL;
}

int avl_tree_put(s_avl_tree *tree, tkey key, void *value)
{
	if (tree == NULL)
	{
		return -1;
	}

	return avl_tree_insert(NULL, &tree->root, key, value);
}

int avl_tree_remove(s_avl_tree *tree, tkey key)
{
	if (tree == NULL)
	{
		return -1;
	}

	return avl_tree_delete(&tree->root, key);
}

void* avl_tree_get(s_avl_tree *tree, tkey key)
{
	return NULL;
}

int avl_tree_insert(s_tree_node *p_node, s_tree_node **node, tkey key, void *value)
{
	if (node == NULL)
	{
		return -1;
	}

	if (*node == NULL)
	{
		s_tree_node *p_new = (s_tree_node *) malloc(sizeof(s_tree_node));
		if (p_new == NULL)
		{
			//printf("[ERROR] Alloc memory failed!\n");
			return -1;
		}
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
		//printf("[ERROR] Find the same key \"%d\"!\n", key);
		return -1;
	}

	if (key < (*node)->key)
	{
		int st = avl_tree_insert(*node, &(*node)->left_child, key, value);
		avl_tree_rebalance(node);
		return st;
	}

	int st = avl_tree_insert(*node, &(*node)->right_child, key, value);
	avl_tree_rebalance(node);
	return st;
}

int avl_tree_delete(s_tree_node **node, tkey key)
{
	if (node == NULL)
	{
		return -1;
	}

	if (*node == NULL)
	{
		return -1;
	}

	//找到关键字相同的节点
	if (key == (*node)->key)
	{
		//删除此节点
		return avl_tree_delete_node(node);
	}
	//如果小于当前节点，则在其左子树上处理
	if (key < (*node)->key)
	{
		int st = avl_tree_delete(&(*node)->left_child, key);
		avl_tree_rebalance(node);
		return st;
	}

	//如果大于当前节点，则在其右子树上处理
	int st = avl_tree_delete(&(*node)->right_child, key);
	avl_tree_rebalance(node);
	return st;
}

int avl_tree_delete_node(s_tree_node **node)
{
	if (node == NULL)
	{
		return -1;
	}

	if (*node == NULL)
	{
		return -1;
	}

	//如果是叶子节点
	if ((*node)->left_child == NULL && (*node)->right_child == NULL)
	{
		s_tree_node *p_del = *node;
		*node = NULL;
		free(p_del);
		return 0;
	}

	//如果只有左子树
	if ((*node)->left_child != NULL && (*node)->right_child == NULL)
	{
		s_tree_node *p_del = *node;
		*node = (*node)->left_child;
		free(p_del);
		return 0;
	}

	//如果只有右子树
	if ((*node)->left_child == NULL && (*node)->right_child != NULL)
	{
		s_tree_node *p_del = *node;
		*node = (*node)->right_child;
		free(p_del);
		return 0;
	}

	//如果平衡因子>=0说明左高右低
	if ((*node)->bf >= 0)
	{
		//找到node节点的左子树中权值最大的节点
		s_tree_node **p_del = avl_tree_find_max_node(&(*node)->left_child);
		avl_tree_node_swap(*node, *p_del);
		return avl_tree_delete_node(p_del);
	}

	//如果平衡因子<0说明左低右高
	//找到node节点的左子树中权值最小的节点
	s_tree_node **p_del = avl_tree_find_min_node(&(*node)->right_child);
	avl_tree_node_swap(*node, *p_del);
	return avl_tree_delete_node(p_del);
}

void avl_tree_node_swap(s_tree_node *node, s_tree_node *node1)
{
	s_tree_node node_temp;

	node_temp.key = node->key;
	node->key = node1->key;
	node1->key = node_temp.key;

	node_temp.value = node->value;
	node->value = node1->value;
	node1->value = node_temp.value;
}

s_tree_node** avl_tree_find_max_node(s_tree_node **node)
{
	if ((*node) == NULL)
	{
		return NULL;
	}
	while ((*node)->right_child != NULL)
	{
		node = &(*node)->right_child;
	}
	return node;
}

s_tree_node** avl_tree_find_min_node(s_tree_node **node)
{
	if (*node == NULL)
	{
		return NULL;
	}
	while ((*node)->left_child != NULL)
	{
		node = &(*node)->left_child;
	}
	return node;
}

void avl_tree_rebalance(s_tree_node **node)
{
	if (node == NULL)
	{
		return;
	}

	if (*node == NULL)
	{
		return;
	}

	(*node)->height = avl_tree_height(*node);
	(*node)->bf = avl_tree_bf(*node);

	if ((*node)->bf > 1 && (*node)->left_child->right_child == NULL)
	{
		avl_tree_single_right(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf > 1 && (*node)->left_child->right_child != NULL)
	{
		avl_tree_left_right(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf < -1 && (*node)->right_child->left_child == NULL)
	{
		avl_tree_single_left(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf < -1 && (*node)->right_child->left_child != NULL)
	{
		avl_tree_right_left(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}
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

void avl_tree_single_right(s_tree_node **node)
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

void avl_tree_single_left(s_tree_node **node)
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

void avl_tree_left_right(s_tree_node **node)
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

void avl_tree_right_left(s_tree_node **node)
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
	if (tree == NULL)
	{
		return;
	}

	if (tree->root == NULL)
	{
		return;
	}

	if (node == NULL)
	{
		return;
	}

	avl_tree_inorder_visit(tree, node->left_child);
	printf("key: %d, height: %d, bf: %d.\n", node->key, node->height, node->bf);
	if (node->bf > 1 || node->bf < -1)
	{
		printf("[ERROR] abs(bf) > 1.\n");
		exit(0);
	}
	avl_tree_inorder_visit(tree, node->right_child);
}

void avl_tree_inorder_display(s_avl_tree *tree, s_tree_node *node, int level)
{
	if (tree == NULL)
	{
		return;
	}

	if (tree->root == NULL)
	{
		return;
	}

	if (node == NULL)
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
