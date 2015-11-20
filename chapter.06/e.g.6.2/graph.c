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

	//初始化顶点
	for (int i = 0; i < vertex_size; i++)
	{
		graph->vertex[i].data = null;
		graph->vertex[i].arccel_out = null;
		graph->vertex[i].arccel_in = null;
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
	s_arccell *arccel_out = (s_arccell *) malloc(sizeof(s_arccell));
	//弧数据
	arccel_out->data = data;
	//权重
	arccel_out->weight = weight;
	//弧尾关联的顶点索引号
	arccel_out->v_index = ev_index;
	arccel_out->next = null;

	//如果顶点中第一条弧为空
	if (graph->vertex[sv_index].arccel_out == null)
	{
		//设置顶点的每一条弧
		graph->vertex[sv_index].arccel_out = arccel_out;
	}
	else
	{
		//找到顶点弧中最后一条弧
		s_arccell *p = graph->vertex[sv_index].arccel_out;
		while (p->next != null)
		{
			p = p->next;
		}
		//追加新弧
		p->next = arccel_out;
	}

	/***
	 * 入弧
	 */
	//新建一个弧
	s_arccell *arccel_in = (s_arccell *) malloc(sizeof(s_arccell));
	//弧数据
	arccel_in->data = data;
	//权重
	arccel_in->weight = weight;
	//弧头关联的顶点索引号
	arccel_in->v_index = sv_index;
	arccel_in->next = null;

	//如果顶点中第一条弧为空
	if (graph->vertex[ev_index].arccel_in == null)
	{
		//设置顶点的每一条弧
		graph->vertex[ev_index].arccel_in = arccel_in;
	}
	else
	{
		//找到顶点弧中最后一条弧
		s_arccell *p = graph->vertex[ev_index].arccel_in;
		while (p->next != null)
		{
			p = p->next;
		}
		//追加新弧
		p->next = arccel_in;
	}
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

		//显示顶点出度弧的权重及数据
		s_arccell *p = graph->vertex[i].arccel_out;
		while (p != null)
		{
			printf(" -> (%d, %d, ", p->v_index, p->weight);
			graph->visit_arccell(p->data);
			printf(") ");
			p = p->next;
		}
		printf("\n");
	}

	printf("\n");

	//循环顶点
	for (int i = 0; i < graph->size; i++)
	{
		//显示顶点索引及数据
		printf("[%d, ", i);
		graph->visit_vertex(graph->vertex[i].data);
		printf("]");

		//显示顶点出度弧的权重及数据
		s_arccell *p = graph->vertex[i].arccel_in;
		while (p != null)
		{
			printf(" -> (%d, %d, ", p->v_index, p->weight);
			graph->visit_arccell(p->data);
			printf(") ");
			p = p->next;
		}
		printf("\n");
	}

	return true;
}
