/*
 * graph.h
 *
 *  Created on: Nov 20, 2015
 *      Author: lidq
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "typedef.h"

//最大正整数
#define INFINITY (0x7FFFFFFF)

//图
typedef struct
{
	//顶点
	int *vertex;
	//边
	int **arccell;
	//顶点个数
	int size;

} s_graph;

//初始化图
bool graph_init(s_graph *graph, int vertex_size);

//销毁图
bool graph_destroy(s_graph *graph);

//设置顶点值
bool graph_set_vertex(s_graph *graph, int index, int val);

//设置边或弧内存的权重
bool graph_set_arccell(s_graph *graph, int i, int j, int weight);

//显示图
bool graph_display(s_graph *graph);

#endif /* GRAPH_H_ */
