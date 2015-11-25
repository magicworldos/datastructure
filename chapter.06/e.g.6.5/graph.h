/*
 * graph.h
 *
 *  Created on: Nov 20, 2015
 *      Author: lidq
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "typedef.h"

//边
typedef struct s_arccell
{
	//权重
	int weight;
	//边头顶点索引号i vertex index
	int i_index;
	//边尾顶点索引号j vertex index
	int j_index;
	//数据
	void *data;
	//下一个与i相关的边结节
	struct s_arccell *next_i;
	//下一个与j相关的边结节
	struct s_arccell *next_j;

} s_arccell;

typedef struct
{
	//顶点数据
	void *data;
	//第一条与此顶点相关的边
	s_arccell *arccel_first;
} s_vertex;

//多重邻接表
typedef struct
{
	//顶点数组
	s_vertex *vertex;
	//顶点个数
	int size;
	//显示顶点数据的回调函数
	void (*visit_vertex)();
	//显示边数据的回调函数
	void (*visit_arccell)();
	s_arccell **arccel_temp;
	s_arccell **arccel_temp2;
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
 * 设置边或边内存的权重
 * int i_index : 顶点i索引
 * int j_index : 顶点j索引
 * int weight   : 权重
 * void *data   : 数据指针
 */
bool graph_insert_arccell(s_graph *graph, int i_index, int j_index, int weight, void *data);

//深度优先访问顶点
bool graph_depth_first_search(s_graph *graph);

//深度优先访问顶点递归算法
void graph_dfs(s_graph *graph, int v_ind, bool *visited);

//显示图信息
bool graph_visit(s_graph *graph);

#endif /* GRAPH_H_ */
