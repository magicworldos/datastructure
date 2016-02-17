/*
 * tree.c
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//初始化树
bool tree_init(s_tree *tree, int m)
{
	if (tree == null)
	{
		return false;
	}

	tree->m = m;
	tree->root = null;

	return true;
}

//销毁树
bool tree_destroy(s_tree *tree)
{
	if (tree == null)
	{
		return false;
	}

	//清空树
	//tree_clear(tree, tree->root);

	//根节点置空
	tree->root = null;

	return true;
}

s_node* tree_search(s_node *node, int key)
{
	if (node == null)
	{
		return null;
	}

	s_pk_node *p = node->pk_node;

	for (int i = 0; i < 2 * node->key_num + 1 && p != null; i++)
	{
		//key
		if (i % 2 == 1)
		{

			if (key == p->pk->key)
			{
				return p->header;
			}
			// <
			else if (key < p->pk->key)
			{
				if (p->pre->pk->child == null)
				{
					return null;
				}
				else
				{
					return tree_search(p->pre->pk->child, key);
				}
			}
			// >
			else
			{
				if ((p->next->next != null && key < p->next->next->pk->key) || (p->next->next == null && p->next->pk->child != null))
				{
					return tree_search(p->next->pk->child, key);
				}
			}

		}
		p = p->next;
	}

	return null;
}

bool tree_insert(s_tree *tree, int key)
{
	return tree_insert_node(tree, null, tree->root, key);
}

bool tree_insert_node(s_tree *tree, s_pk_node *pk_node, s_node *node, int key)
{
	if (tree == null)
	{
		return false;
	}

	if (node == null)
	{
		node = (s_node *) malloc(sizeof(s_node));
		node->parent = pk_node;
		node->key_num = 0;
		node->pk_node = null;

		if (pk_node != null)
		{
			pk_node->pk->child = node;
		}

		if (tree->root == null)
		{
			tree->root = node;
		}
	}

	if (node->key_num == 0)
	{
		s_point_key *pk_pre = (s_point_key *) malloc(sizeof(s_point_key));
		pk_pre->child = null;

		s_point_key *pk_key = (s_point_key *) malloc(sizeof(s_point_key));
		pk_key->key = key;

		s_point_key *pk_next = (s_point_key *) malloc(sizeof(s_point_key));
		pk_next->child = null;

		s_pk_node *pk_node_pre = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_pre->header = node;
		pk_node_pre->pk = pk_pre;

		s_pk_node *pk_node_key = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_key->header = node;
		pk_node_key->pk = pk_key;

		s_pk_node *pk_node_next = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_next->header = node;
		pk_node_next->pk = pk_next;

		pk_node_pre->pre = null;
		pk_node_pre->next = pk_node_key;

		pk_node_key->pre = pk_node_pre;
		pk_node_key->next = pk_node_next;

		pk_node_next->pre = pk_node_key;
		pk_node_next->next = null;

		node->pk_node = pk_node_pre;

		node->key_num++;

		return true;
	}

	s_pk_node *p = node->pk_node;

	for (int i = 0; i < 2 * node->key_num + 1 && p != null; i++)
	{
		//key
		if (i % 2 == 1)
		{

			if (key == p->pk->key)
			{
				return true;
			}
			// <
			else if (key < p->pk->key)
			{
				if (p->pre->pk->child == null)
				{
					tree_insert_pk_node(p, 0, key);
					node->key_num++;
					tree_split_node(tree, node);

					return true;
				}
				else
				{
					return tree_insert_node(tree, p->pre, p->pre->pk->child, key);
				}
			}
			// >
			else
			{
				if ((p->next->next != null && key < p->next->next->pk->key && p->next->pk->child == null) || (p->next->next == null && p->next->pk->child == null))
				{
					tree_insert_pk_node(p, 1, key);
					node->key_num++;
					tree_split_node(tree, node);

					return true;
				}
				else if (p->next->next != null && key < p->next->next->pk->key && p->next->pk->child != null)
				{
					return tree_insert_node(tree, p->next, p->next->pk->child, key);
				}
				else if (p->next->next == null && p->next->pk->child != null)
				{
					return tree_insert_node(tree, p->next, p->next->pk->child, key);
				}
			}

		}
		p = p->next;
	}

	return true;
}

void tree_insert_pk_node(s_pk_node *pk_node, int type, int key)
{
	if (type == 0)
	{
		s_point_key *pk_key = (s_point_key *) malloc(sizeof(s_point_key));
		pk_key->key = key;

		s_point_key *pk_pre = (s_point_key *) malloc(sizeof(s_point_key));
		pk_pre->child = null;

		s_pk_node *pk_node_key = (s_pk_node *) malloc(sizeof(s_pk_node));
		s_pk_node *pk_node_pre = (s_pk_node *) malloc(sizeof(s_pk_node));

		pk_node_key->header = pk_node->header;
		pk_node_key->pk = pk_key;
		pk_node_pre->header = pk_node->header;
		pk_node_pre->pk = pk_pre;

		pk_node_pre->pre = pk_node->pre->pre;
		pk_node->pre->pre = pk_node_key;
		pk_node_key->next = pk_node->pre;
		pk_node_key->pre = pk_node_pre;
		pk_node_pre->next = pk_node_key;
		if (pk_node_pre->pre != null)
		{
			pk_node_pre->pre->next = pk_node_pre;
		}
		else
		{
			pk_node->header->pk_node = pk_node_pre;
		}
		pk_node_pre->header = pk_node->header;
		pk_node_key->header = pk_node->header;
	}
	//next
	else if (type == 1)
	{
		s_point_key *pk_key = (s_point_key *) malloc(sizeof(s_point_key));
		pk_key->key = key;

		s_point_key *pk_next = (s_point_key *) malloc(sizeof(s_point_key));
		pk_next->child = null;

		s_pk_node *pk_node_key = (s_pk_node *) malloc(sizeof(s_pk_node));
		s_pk_node *pk_node_next = (s_pk_node *) malloc(sizeof(s_pk_node));

		pk_node_key->header = pk_node->header;
		pk_node_key->pk = pk_key;
		pk_node_next->header = pk_node->header;
		pk_node_next->pk = pk_next;

		pk_node_next->next = pk_node->next->next;
		pk_node->next->next = pk_node_key;
		pk_node_key->pre = pk_node->next;
		pk_node_key->next = pk_node_next;
		pk_node_next->pre = pk_node_key;
		if (pk_node_next->next != null)
		{
			pk_node_next->next->pre = pk_node_next;
		}

		pk_node_key->header = pk_node->header;
		pk_node_next->header = pk_node->header;
	}
}

void tree_split_node(s_tree *tree, s_node *node)
{
	if (node->key_num < tree->m)
	{
		return;
	}

	s_pk_node *pk_parent = node->parent;

	int m = node->key_num;

	int p_num = divup(m, 2) - 1;
	s_node *p = (s_node *) malloc(sizeof(s_node));
	p->key_num = p_num;
	p->parent = pk_parent;
	p->pk_node = node->pk_node;

	s_pk_node *p_pk = node->pk_node;
	for (int i = 0; i < p_num; i++)
	{
		//pointer
		p_pk->header = p;
		p_pk = p_pk->next;
		//key
		p_pk->header = p;
		p_pk = p_pk->next;
	}

	s_pk_node *r = p_pk->next;

	p_pk->header = p;
	p_pk->next->pre = null;
	p_pk->next = null;

	s_node *q = node;
	int q_num = m - divup(m, 2);
	q->parent = pk_parent;
	q->key_num = q_num;
	q->pk_node = r->next;
	q->pk_node->pre = null;

	s_pk_node *q_pk = node->pk_node;
	for (int i = 0; i < q_num; i++)
	{
		//pointer
		q_pk->header = q;
		q_pk = q_pk->next;
		//key
		q_pk->header = q;
		q_pk = q_pk->next;
	}

	if (q_pk != null)
	{
		q_pk->header = q;
	}

	r->pre = null;
	r->next = null;

	if (pk_parent == null)
	{
		s_node *p_new = (s_node *) malloc(sizeof(s_node));
		p_new->parent = null;
		p_new->key_num = 0;
		p_new->pk_node = null;

		tree->root = p_new;

		s_point_key *pk_pre = (s_point_key *) malloc(sizeof(s_point_key));
		pk_pre->child = p;

		s_point_key *pk_next = (s_point_key *) malloc(sizeof(s_point_key));
		pk_next->child = q;

		s_pk_node *pk_node_pre = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_pre->header = p_new;
		pk_node_pre->pk = pk_pre;

		s_pk_node *pk_node_next = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_next->header = p_new;
		pk_node_next->pk = pk_next;

		pk_node_pre->pre = null;
		pk_node_pre->next = r;

		r->pre = pk_node_pre;
		r->next = pk_node_next;
		r->header = p_new;

		pk_node_next->pre = r;
		pk_node_next->next = null;

		p->parent = pk_node_pre;
		q->parent = pk_node_next;

		p_new->pk_node = pk_node_pre;
		p_new->key_num++;

		node = p_new;
	}
	else
	{
		s_point_key *pk_next = (s_point_key *) malloc(sizeof(s_point_key));
		s_pk_node *pk_node_next = (s_pk_node *) malloc(sizeof(s_pk_node));
		pk_node_next->pk = pk_next;

		r->next = pk_node_next;
		pk_node_next->pre = r;
		pk_node_next->next = pk_parent->next;
		pk_node_next->header = pk_parent->header;

		if (pk_parent->next != null)
		{
			pk_parent->next->pre = pk_node_next;
		}

		pk_parent->pk->child = p;
		pk_parent->next = r;
		r->pre = pk_parent;
		r->header = pk_parent->header;

		q->parent = pk_node_next;
		pk_node_next->pk->child = q;

		pk_parent->header->key_num++;

		node = pk_parent->header;
	}

	tree_split_node(tree, node);
}

bool tree_del(s_tree *tree, int key)
{
	return tree_del_node(tree, tree->root, key);
}

bool tree_del_node(s_tree *tree, s_node *node, int key)
{
	if (tree == null)
	{
		return false;
	}

	if (node == null)
	{
		return false;
	}

	s_node *p_del = tree_search(node, key);
	if (p_del == null)
	{
		return false;
	}

	s_pk_node *pk_node_del = tree_find_pk_node(p_del, key);
	if (pk_node_del == null)
	{
		return false;
	}

	if (!tree_is_leaf(p_del))
	{
		s_pk_node *pk_node_min = null;
		if (pk_node_del->next->pk->child == null)
		{
			pk_node_min = pk_node_del->next->next;
		}
		else
		{
			pk_node_min = tree_min_key(pk_node_del->next->pk->child);
		}

		if (pk_node_min == null)
		{
			return false;
		}

		pk_node_del->pk->key = pk_node_min->pk->key;

		tree_del_node(tree, pk_node_min->header, pk_node_min->pk->key);
	}

	int num = divup(tree->m, 2);
	if (p_del->key_num >= num)
	{
		s_pk_node *pre = pk_node_del->pre;
		pre->next = pk_node_del->next->next;
		if (pre->next != null)
		{
			pre->next->pre = pre;
		}

		p_del->key_num--;
		return true;
	}

//	if (p_del->key_num == num - 1)
//	{
//		//
//		//
//		//
//		return true;
//	}

	return true;
}

int divup(int a, int b)
{
	int c = a / b;
	int d = a % b;
	if (d != 0)
	{
		c++;
	}
	return c;
}

bool tree_is_leaf(s_node *node)
{
	s_pk_node *pk_node = node->pk_node;
	for (int i = 0; i < 2 * node->key_num + 1 && pk_node != null; i++)
	{
		if (i % 2 == 0)
		{
			if (pk_node->pk->child != null)
			{
				return false;
			}
		}
		pk_node = pk_node->next;
	}

	return true;
}

s_pk_node* tree_find_pk_node(s_node *node, int key)
{
	if (node == null)
	{
		return null;
	}

	s_pk_node *p = node->pk_node;
	for (int i = 0; i < 2 * node->key_num + 1 && p != null; i++)
	{
		if (i % 2 == 1)
		{
			if (p->pk->key == key)
			{
				return p;
			}
		}
		p = p->next;
	}

	return null;
}

s_pk_node* tree_min_key(s_node *node)
{
	if (node == null)
	{
		return null;
	}

	s_pk_node *pk_node = node->pk_node;
	if (pk_node == null)
	{
		return null;
	}

	if (pk_node->pk->child == null)
	{
		return pk_node->next;
	}

	return tree_min_key(pk_node->pk->child);
}
