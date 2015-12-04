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
bool graph_init(s_graph *graph, int vertex_size, void (*visit_vertex)(), void (*visit_arccell)())
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
	graph->vertex = (s_vertex *) malloc(sizeof(s_vertex) * vertex_size);
	graph->arccel_temp = (s_arccell **) malloc(sizeof(s_arccell *) * vertex_size);
	graph->arccel_temp2 = (s_arccell **) malloc(sizeof(s_arccell *) * vertex_size);
	//初始化顶点
	for (int i = 0; i < vertex_size; i++)
	{
		graph->vertex[i].data = null;
		graph->vertex[i].arccel_first = null;

		graph->arccel_temp[i] = null;
		graph->arccel_temp2[i] = null;
	}

	//显示顶点数据的回调函数
	graph->visit_vertex = visit_vertex;
	//显示边数据的回调函数
	graph->visit_arccell = visit_arccell;

	return true;
}

//销毁图
bool graph_destroy(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	free(graph->vertex);

	free(graph->arccel_temp);
	free(graph->arccel_temp2);

	return true;
}

/*
 * 设置顶点数据
 * int index  : 顶点索引号
 * void *data : 数据指针
 */
bool graph_set_vertex(s_graph *graph, int index, void *data)
{
	if (graph == null)
	{
		return false;
	}

	graph->vertex[index].data = data;

	return true;
}

/*
 * 设置边或边内存的权重
 * int i_index : 顶点i索引
 * int j_index : 顶点j索引
 * int weight   : 权重
 * void *data   : 数据指针
 */
bool graph_insert_arccell(s_graph *graph, int i_index, int j_index, int weight, void *data)
{
	if (graph == null)
	{
		return false;
	}

	if (i_index < 0 || i_index >= graph->size)
	{
		return false;
	}

	if (j_index < 0 || j_index >= graph->size)
	{
		return false;
	}

	/***
	 * 出入边
	 */
	//新建一个边
	s_arccell *arccel = (s_arccell *) malloc(sizeof(s_arccell));
	//边数据
	arccel->data = data;
	//权重
	arccel->weight = weight;
	//边尾关联的顶点索引号
	arccel->i_index = i_index;
	arccel->j_index = j_index;
	arccel->next_i = null;
	arccel->next_j = null;

	//如果顶点中第一条边为空
	if (graph->vertex[i_index].arccel_first == null)
	{
		//设置顶点的每一条边
		graph->vertex[i_index].arccel_first = arccel;
	}

	if (graph->vertex[j_index].arccel_first == null)
	{
		//设置顶点的每一条边
		graph->vertex[j_index].arccel_first = arccel;
	}

	if (graph->arccel_temp[j_index] != null)
	{
		graph->arccel_temp[j_index]->next_j = arccel;
	}
	graph->arccel_temp[j_index] = arccel;

	if (graph->arccel_temp[i_index] != null)
	{
		graph->arccel_temp[i_index]->next_i = arccel;
	}
	graph->arccel_temp[i_index] = arccel;

	return true;
}

//显示图信息
bool graph_visit(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	//循环顶点
	for (int i = 0; i < graph->size; i++)
	{
		//显示顶点索引及数据
		printf("[%d, ", i);
		graph->visit_vertex(graph->vertex[i].data);
		printf("]");
		s_arccell *p = graph->vertex[i].arccel_first;
		if (p != null)
		{
			printf(" -> (%d, %d, %d, ", p->i_index, p->j_index, p->weight);
			graph->visit_arccell(p->data);
			printf(") ");
		}
		printf("\n");
	}

	printf("\n\n");

	//循环顶点
	for (int i = 0; i < graph->size; i++)
	{
		//显示顶点索引及数据
		printf("[%d, ", i);
		graph->visit_vertex(graph->vertex[i].data);
		printf("]");

		//显示顶点出度边的权重及数据
		s_arccell *p = graph->vertex[i].arccel_first;
		while (p != null)
		{
			printf(" --> {%d, %d, %d, ", p->i_index, p->j_index, p->weight);
			graph->visit_arccell(p->data);

			s_arccell *q = p->next_j;
			while (q != null)
			{
				printf(" -> (%d, %d, %d, ", q->i_index, q->j_index, q->weight);
				graph->visit_arccell(q->data);
				printf(") ");
				q = q->next_j;
			}
			p = p->next_i;
			printf("} ");
		}
		printf("\n");
	}

	printf("\n");

	return true;
}

//深度优先搜索
bool graph_depth_first_search(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	//设置顶点已访问标志
	bool visited[graph->size];
	for (int i = 0; i < graph->size; i++)
	{
		visited[i] = false;
	}

	//访问所有的顶点
	for (int i = 0; i < graph->size; i++)
	{
		//深度优先访问顶点
		graph_dfs(graph, i, visited);
	}

	return true;
}

//深度优先访问顶点递归算法
void graph_dfs(s_graph *graph, int v_ind, bool *visited)
{
	//如果此顶点已被访问，则直接返回
	if (visited[v_ind])
	{
		return;
	}

	//设置此顶点为已访问
	visited[v_ind] = true;

	//调用访问回调函数访问此节点
	graph->visit_vertex(graph->vertex[v_ind]);

	//取得下一条边
	s_arccell *ac = graph->vertex[v_ind].arccel_first;
	//循环所有关联i的边
	while (ac != null)
	{
		//深度优先访问
		graph_dfs(graph, ac->i_index, visited);

		//如果还有下一条j相关的边
		s_arccell *ac_p = graph->vertex[ac->j_index].arccel_first;
		while (ac_p != null)
		{
			//深度优先访问
			graph_dfs(graph, ac_p->j_index, visited);
			ac_p = ac_p->next_j;
		}

		//下一条i边
		ac = ac->next_i;
	}

}

void free_int(int *i)
{
	if (i != null)
	{
		free(i);
	}
}

//广度优先搜索
bool graph_breadth_first_search(s_graph *graph)
{
	if (graph == null)
	{
		return false;
	}

	//设置队列
	s_queue queue;
	init_queue(&queue, sizeof(int), free_int, null);

	//设置顶点已访问标志
	bool visited[graph->size];
	for (int i = 0; i < graph->size; i++)
	{
		visited[i] = false;
	}

	//访问所有的顶点
	for (int i = 0; i < graph->size; i++)
	{
		//深度广先访问顶点
		graph_bfs(graph, i, visited, &queue);
	}

	//销毁队列
	destroy_queue(&queue);

	return true;
}

//广度优先访问顶点递归算法
void graph_bfs(s_graph *graph, int v_ind, bool *visited, s_queue *queue)
{
	//如果此顶点已被访问，则直接返回
	if (visited[v_ind])
	{
		return;
	}

	//设置此顶点为已访问
	visited[v_ind] = true;

	//调用访问回调函数访问此节点
	graph->visit_vertex(graph->vertex[v_ind]);

	//取得下一条边
	s_arccell *ac = graph->vertex[v_ind].arccel_first;
	//循环所有关联i的边
	while (ac != null)
	{
		//将此顶点的关联顶点加入队列
		int *ival = malloc(sizeof(int));
		*ival = ac->i_index;
		queue_in(queue, ival);

		//如果还有下一条j相关的边
		s_arccell *ac_p = graph->vertex[ac->j_index].arccel_first;
		while (ac_p != null)
		{
			//将此顶点的关联顶点加入队列
			int *jval = malloc(sizeof(int));
			*jval = ac_p->j_index;
			queue_in(queue, jval);

			ac_p = ac_p->next_j;
		}

		//下一条i边
		ac = ac->next_i;
	}

	//如果队列不为空，即：出队列成功
	int *vertex = null;
	if (queue_out(queue, (void**) &vertex))
	{
		//对此顶点进行广度优先搜索
		graph_bfs(graph, *vertex, visited, queue);
	}
}
