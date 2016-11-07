/*
 * avl_tree.c
 *
 *  Created on: Nov 4, 2016
 *      Author: lidq
 */

#include <avl_tree.h>

//初始化平衡二叉树
int avl_tree_init(s_avl_tree *tree)
{
	if (tree == NULL)
	{
		return -1;
	}

	tree->root = NULL;

	return 0;
}

//销毁平衡二叉树
int avl_tree_destroy(s_avl_tree *tree)
{
	if (tree == NULL)
	{
		return -1;
	}

	//递归清空子节点
	avl_tree_clear(&tree->root);

	return 0;
}

//递归清空子节点
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

	//递归清空左子树
	avl_tree_clear(&(*node)->left_child);
	//递归清空右子树
	avl_tree_clear(&(*node)->right_child);

	(*node)->left_child = NULL;
	(*node)->right_child = NULL;

	free(*node);
	*node = NULL;
}

//插入新数据
int avl_tree_put(s_avl_tree *tree, tkey key, void *value)
{
	if (tree == NULL)
	{
		return -1;
	}
	//递归插入
	return avl_tree_insert(&tree->root, key, value);
}

//移除数据
int avl_tree_remove(s_avl_tree *tree, tkey key)
{
	if (tree == NULL)
	{
		return -1;
	}
	//递归移除节点
	return avl_tree_delete(&tree->root, key);
}

//二叉树查找取得关键字的值
void* avl_tree_get(s_avl_tree *tree, tkey key)
{
	return avl_tree_get_value(tree->root, key);
}

//二叉树查找取得关键字的值
void* avl_tree_get_value(s_tree_node *node, tkey key)
{
	if (node == NULL)
	{
		return NULL;
	}

	//找到相同的关键字
	if (key == node->key)
	{
		return node->value;
	}

	//如果关键字小，在其左子树上处理
	if (key < node->key)
	{
		return avl_tree_get_value(node->left_child, key);
	}

	//如果关键字大，在其右子树上处理
	return avl_tree_get_value(node->right_child, key);
}

//递归插入数据
int avl_tree_insert(s_tree_node **node, tkey key, void *value)
{
	if (node == NULL)
	{
		return -1;
	}

	if (*node == NULL)
	{
		//创建新节点
		s_tree_node *p_new = (s_tree_node *) malloc(sizeof(s_tree_node));
		if (p_new == NULL)
		{
			//printf("[ERROR] Alloc memory failed!\n");
			return -1;
		}
		p_new->key = key;
		p_new->value = value;
		p_new->bf = 0;
		p_new->height = 0;
		p_new->left_child = NULL;
		p_new->right_child = NULL;
		*node = p_new;

		return 0;
	}

	//找到相同的关键字
	if (key == (*node)->key)
	{
		//printf("[ERROR] Find the same key \"%d\"!\n", key);
		return -1;
	}

	//如果关键字小，在其左子树上处理
	if (key < (*node)->key)
	{
		int st = avl_tree_insert(&(*node)->left_child, key, value);
		//平衡处理
		avl_tree_rebalance(node);
		return st;
	}

	//如果关键字大，在其右子树上处理
	int st = avl_tree_insert(&(*node)->right_child, key, value);
	//平衡处理
	avl_tree_rebalance(node);
	return st;
}

//删除关键字节点
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
		//平衡处理
		avl_tree_rebalance(node);
		return st;
	}

	//如果大于当前节点，则在其右子树上处理
	int st = avl_tree_delete(&(*node)->right_child, key);
	//平衡处理
	avl_tree_rebalance(node);
	return st;
}

//删除节点
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

//交换两个节点的关键字和值
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

//找到子树中关键字最大的节点
s_tree_node** avl_tree_find_max_node(s_tree_node **node)
{
	if ((*node) == NULL)
	{
		return NULL;
	}
	//由于是二叉排序树，右孩子节点关键字最大
	while ((*node)->right_child != NULL)
	{
		node = &(*node)->right_child;
	}
	return node;
}

//找到子树中关键字最小的节点
s_tree_node** avl_tree_find_min_node(s_tree_node **node)
{
	if (*node == NULL)
	{
		return NULL;
	}
	//由于是二叉排序树，左孩子节点关键字最小
	while ((*node)->left_child != NULL)
	{
		node = &(*node)->left_child;
	}
	return node;
}

//二叉树的平衡处理
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

	//计算节点高（深度）
	(*node)->height = avl_tree_height(*node);
	//计算节点的平衡因子（左子树高减去右子树高）
	(*node)->bf = avl_tree_bf(*node);

	if ((*node)->bf > 1 && (*node)->left_child->right_child == NULL)
	{
		//单向右旋
		avl_tree_single_right(node);
		//对处理后的节点再做平衡处理
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf > 1 && (*node)->left_child->right_child != NULL)
	{
		//先左旋再右旋
		avl_tree_left_right(node);
		//对处理后的节点再做平衡处理
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf < -1 && (*node)->right_child->left_child == NULL)
	{
		//单向左旋
		avl_tree_single_left(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		//对处理后的节点再做平衡处理
		avl_tree_rebalance(node);
		return;
	}

	if ((*node)->bf < -1 && (*node)->right_child->left_child != NULL)
	{
		//先右旋再左旋
		avl_tree_right_left(node);
		avl_tree_rebalance(&(*node)->left_child);
		avl_tree_rebalance(&(*node)->right_child);
		//对处理后的节点再做平衡处理
		avl_tree_rebalance(node);
		return;
	}
}

//计算节点的高（深度）
int avl_tree_height(s_tree_node *node)
{
	if (node == NULL)
	{
		return -1;
	}
	//递归计算左子树高
	int height_left = avl_tree_height(node->left_child);
	//递归计算右子树高
	int height_right = avl_tree_height(node->right_child);
	//左右子树较大的一侧的高度加一
	return height_left > height_right ? height_left + 1 : height_right + 1;
}

//计算平衡因子，左子树高减去右子树高
int avl_tree_bf(s_tree_node *node)
{
	if (node == NULL)
	{
		return 0;
	}
	//左右子树为空
	if (node->left_child == NULL && node->right_child == NULL)
	{
		return 0;
	}
	//只有左子树
	if (node->left_child != NULL && node->right_child == NULL)
	{
		return node->height;
	}
	//只有右子树
	if (node->left_child == NULL && node->right_child != NULL)
	{
		return -(node->height);
	}
	//左子树高减去右子树高
	return node->left_child->height - node->right_child->height;
}

//单向右旋
void avl_tree_single_right(s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->left_child;
	s_tree_node **pC = &(*pB)->right_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	//平衡旋转
	*pB = nC;
	*pC = nA;
	*pA = nB;

	//重新计算树高和平衡因子
	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
}

//单向左旋
void avl_tree_single_left(s_tree_node **node)
{
	s_tree_node **pA = node;
	s_tree_node **pB = &(*pA)->right_child;
	s_tree_node **pC = &(*pB)->left_child;

	s_tree_node *nA = *pA;
	s_tree_node *nB = *pB;
	s_tree_node *nC = *pC;

	//平衡旋转
	*pB = nC;
	*pC = nA;
	*pA = nB;

	//重新计算树高和平衡因子
	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
}

//先左旋再右旋
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

	//平衡旋转
	*pC = nC->left_child;
	*pB = nC->right_child;
	*pD = nB;
	*pE = nA;
	*pA = nC;

	//重新计算树高和平衡因子
	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nC->height = avl_tree_height(nC);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
	nC->bf = avl_tree_bf(nC);
}

//先右旋再左旋
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

	//平衡旋转
	*pB = nC->left_child;
	*pC = nC->right_child;
	*pD = nA;
	*pE = nB;
	*pA = nC;

	//重新计算树高和平衡因子
	nA->height = avl_tree_height(nA);
	nB->height = avl_tree_height(nB);
	nC->height = avl_tree_height(nC);
	nA->bf = avl_tree_bf(nA);
	nB->bf = avl_tree_bf(nB);
	nC->bf = avl_tree_bf(nC);
}

//前序遍历
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
	printf("key: %d, value: %d, height: %d, bf: %d.\n", node->key, node->value == NULL ? -1 : *(int *) node->value, node->height, node->bf);
//	if (node->bf > 1 || node->bf < -1)
//	{
//		printf("[ERROR] abs(bf) > 1.\n");
//		exit(0);
//	}
	avl_tree_inorder_visit(tree, node->right_child);
}

//按树型结构显示平衡二叉树
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
