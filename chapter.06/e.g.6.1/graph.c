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
