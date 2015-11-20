/*
 * graph.h
 *
 *  Created on: Nov 20, 2015
 *      Author: lidq
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "typedef.h"

//边或弧
typedef struct s_arccell
{
	//权重
	int weight;
	//弧头顶点索引号start vertex index
	int sv_index;
	//弧尾顶点索引号end vertex index
	int ev_index;
	//数据
	void *data;
	//下一个同头弧结节
	struct s_arccell *next_h;
	//下一个同尾弧结节
	struct s_arccell *next_f;

} s_arccell;

typedef struct
{
	//顶点数据
	void *data;
	//出弧，以当前顶点为起始的弧
	s_arccell *arccel_out;
	//入弧，以当前顶点为终止的弧
	s_arccell *arccel_in;
} s_vertex;

//十字链表
typedef struct
{
	//顶点数组
	s_vertex *vertex;
	//构建十字链表辅助数组
	s_arccell **arccel_temp;
	//顶点个数
	int size;
	//显示顶点数据的回调函数
	void (*visit_vertex)();
	//显示弧数据的回调函数
	void (*visit_arccell)();
} s_graph;

//初始化图
bool graph_init(s_graph *graph, int vertex_size, void (*visit_vertex)(), void (*visit_arccell)());

//销毁图
bool graph_destroy(s_graph *graph);

/*
 * 设置顶点数据
 * int index  : 顶点索引号
 * void *data : 数据指针
 */
bool graph_set_vertex(s_graph *graph, int index, void *data);

/*
 * 设置边或弧内存的权重
 * int sv_index : 起始顶点索引
 * int ev_index : 终止顶点索引
 * int weight   : 权重
 * void *data   : 数据指针
 */
bool graph_insert_arccell(s_graph *graph, int sv_index, int ev_index, int weight, void *data);

//显示图信息
bool graph_visit(s_graph *graph);

#endif /* GRAPH_H_ */
