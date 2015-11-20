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
	//申请辅助内存
	graph->arccel_temp = (s_arccell **) malloc(sizeof(s_arccell *) * vertex_size);

	//初始化顶点
	for (int i = 0; i < vertex_size; i++)
	{
		graph->vertex[i].data = null;
		graph->vertex[i].arccel_out = null;
		graph->vertex[i].arccel_in = null;

		graph->arccel_temp[i] = null;
	}

	//显示顶点数据的回调函数
	graph->visit_vertex = visit_vertex;
	//显示弧数据的回调函数
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
 * 设置边或弧内存的权重及数据
 * int sv_index : 起始顶点索引
 * int ev_index : 终止顶点索引
 * int weight   : 权重
 * void *data   : 数据指针
 */
bool graph_insert_arccell(s_graph *graph, int sv_index, int ev_index, int weight, void *data)
{
	if (graph == null)
	{
		return false;
	}

	if (sv_index < 0 || sv_index >= graph->size)
	{
		return false;
	}

	if (ev_index < 0 || ev_index >= graph->size)
	{
		return false;
	}

	/***
	 * 出入弧
	 */
	//新建一个弧
	s_arccell *arccel = (s_arccell *) malloc(sizeof(s_arccell));
	//弧数据
	arccel->data = data;
	//权重
	arccel->weight = weight;
	//弧尾关联的顶点索引号
	arccel->sv_index = sv_index;
	arccel->ev_index = ev_index;
	arccel->next_h = null;
	arccel->next_f = null;

	//如果顶点中第一条弧为空
	if (graph->vertex[sv_index].arccel_out == null)
	{
		//设置顶点的每一条弧
		graph->vertex[sv_index].arccel_out = arccel;
	}
	else
	{
		//找到顶点弧中最后一条弧
		s_arccell *p = graph->vertex[sv_index].arccel_out;
		while (p->next_h != null)
		{
			p = p->next_h;
		}
		//追加新弧
		p->next_h = arccel;
	}

	//设置顶点的入弧
	if (graph->vertex[ev_index].arccel_in == null)
	{
		graph->vertex[ev_index].arccel_in = arccel;
	}

	//设置下一条同终止顶点指针
	if (graph->arccel_temp[ev_index] != null)
	{
		graph->arccel_temp[ev_index]->next_f = arccel;
	}
	graph->arccel_temp[ev_index] = arccel;

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
		s_arccell *p = graph->vertex[i].arccel_in;
		if (p != null)
		{
			printf(" -> (%d, %d, %d, ", p->sv_index, p->ev_index, p->weight);
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

		//显示顶点出度弧的权重及数据
		s_arccell *p = graph->vertex[i].arccel_out;
		while (p != null)
		{
			printf(" --> {%d, %d, %d, ", p->sv_index, p->ev_index, p->weight);
			graph->visit_arccell(p->data);

			s_arccell *q = p->next_f;
			while (q != null)
			{
				printf(" -> (%d, %d, %d, ", q->sv_index, q->ev_index, q->weight);
				graph->visit_arccell(q->data);
				printf(") ");
				q = q->next_f;
			}
			p = p->next_h;
			printf("} ");
		}
		printf("\n");
	}

	printf("\n");

	return true;
}
