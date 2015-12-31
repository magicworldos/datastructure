/*
 * graph.c
 *
 *  Created on: Nov 20, 2015
 *      Author: lidq
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//初始化图
bool graph_init(s_graph *graph, int vertex_size)
{
	if (graph == null)
	{
		return false;
	}

	if (vertex_size <= 0)
	{
		return false;
	}

	//设置顶点个数
	graph->size = vertex_size;
	//申请顶点内存
	graph->vertex = (int *) malloc(sizeof(int) * vertex_size);
	//申请边或弧内存
	graph->arccell = (int **) malloc(sizeof(int *) * vertex_size);

	for (int i = 0; i < vertex_size; i++)
	{
		//顶点值默认为0
		graph->vertex[i] = 0;
		graph->arccell[i] = malloc(sizeof(int) * vertex_size);
		for (int j = 0; j < vertex_size; j++)
		{
			//边的权重默认为无穷大
			graph->arccell[i][j] = INFINITY;
		}
	}

	return true;
}

//销毁图
bool graph_destroy(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	for (int i = 0; i < graph->size; i++)
	{
		free(graph->arccell[i]);
	}
	free(graph->arccell);
	free(graph->vertex);

	return true;
}

//设置顶点值
bool graph_set_vertex(s_graph *graph, int index, int val)
{
	if (graph == null)
	{
		return false;
	}

	graph->vertex[index] = val;

	return true;
}

//设置边或弧内存的权重
bool graph_set_arccell(s_graph *graph, int i, int j, int weight)
{
	if (graph == null)
	{
		return false;
	}

	graph->arccell[i][j] = weight;

	return true;
}

//显示图
bool graph_display(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	for (int i = 0; i < graph->size; i++)
	{
		printf("%d ", graph->vertex[i]);
	}
	printf("\n\n");

	for (int i = 0; i < graph->size; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			if (graph->arccell[i][j] == INFINITY)
			{
				printf(" --, ");
			}
			else
			{
				printf("%3d, ", graph->arccell[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");

	return true;
}

//最短路径
void graph_shortest_path(s_graph *graph)
{
	int weights[graph->size][graph->size];
	int paths[graph->size][graph->size];
	int mini_weight[graph->size];
	int mini_index[graph->size];
	int s[graph->size];
	int find[graph->size];

	for (int i = 0; i < graph->size; ++i)
	{
		s[i] = -1;
		mini_weight[i] = INFINITY;
		mini_index[i] = -1;
		find[i] = 0;
		for (int j = 0; j < graph->size; ++j)
		{
			weights[i][j] = INFINITY;
		}

	}

	insert_to_s(s, 0);
	find[0] = 1;
//	printf("mini index: %d\n", 0);
//	print_s(s, 1);

	int ind = 0;
	int i = 0;
	while (ind < graph->size)
	{
		if (mini_index[i] != -1)
		{
			i = mini_index[i];
		}

		//for (int i = 0; i < graph->size; ++i)
		{
			{
				if (i == 0)
				{
					for (int j = i + 1; j < graph->size; ++j)
					{
						//printf("aa %d %d\n", i, j);
						weights[i][j] = graph->arccell[i][j];
						if (weights[i][j] < mini_weight[i])
						{
							//printf("fffffffff %d %d\n", i, j);
							mini_weight[i] = weights[i][j];
							mini_index[i] = j;
						}
					}
				}
				else
				{
					for (int j = ind; j < graph->size; ++j)
					{
						//if (find[j] == 0)
						{
							if (ind == 2)
							{
								printf("bb %d %d\n", i, j);
								printf("%d %d %d\n", graph->arccell[i][j], weights[ind - 1][mini_index[ind - 1]], weights[ind - 1][j]);
							}
							if (graph->arccell[i][j] + weights[ind - 1][mini_index[ind - 1]] < weights[ind - 1][j])
							{
								weights[ind][j] = graph->arccell[i][j] + weights[ind - 1][mini_index[ind - 1]];
							}
							else
							{
								weights[ind][j] = weights[ind - 1][j];
							}

							if (weights[ind][j] < mini_weight[ind])
							{
								//if (ind == 2)
								{
									printf("ccc %d %d %d\n", graph->arccell[i][j], weights[ind - 1][mini_index[ind - 1]], weights[ind - 1][j]);
								}
								mini_weight[ind] = weights[ind][j];
								mini_index[ind] = j;
							}
						}
					}
				}
				if (find[mini_index[ind]] == 0)
				{
					insert_to_s(s, mini_index[ind]);
					printf("i: %d\tw: %d\n", mini_index[ind], mini_weight[ind]);
					print_s(s, ind + 2);
				}
				find[mini_index[ind]] = 1;
				ind++;
			}
		}
	}
}

void insert_to_s(int *s, int ind)
{
	while (*s != -1)
	{
		s++;
	}
	*s = ind;
}

void print_s(int *s, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", s[i]);
	}
	printf("\n");
}
