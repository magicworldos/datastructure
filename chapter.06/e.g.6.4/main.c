#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void visit_int(int *i)
{
	if (i != null)
	{
		printf("%d", *i);
	}
}

int main(int argc, char **args)
{
	//邻接表
	s_graph graph;
	graph_init(&graph, 5, &visit_int, &visit_int);

	//顶点数据项
	int *t0 = (int *) malloc(sizeof(int));
	int *t1 = (int *) malloc(sizeof(int));
	int *t2 = (int *) malloc(sizeof(int));
	int *t3 = (int *) malloc(sizeof(int));
	int *t4 = (int *) malloc(sizeof(int));
	//顶点数据
	*t0 = 53;
	*t1 = 43;
	*t2 = 12;
	*t3 = 54;
	*t4 = 75;
	//边数据项
	int *d0 = (int *) malloc(sizeof(int));
	int *d1 = (int *) malloc(sizeof(int));
	int *d2 = (int *) malloc(sizeof(int));
	int *d3 = (int *) malloc(sizeof(int));
	int *d4 = (int *) malloc(sizeof(int));
	int *d5 = (int *) malloc(sizeof(int));
	//边数据
	*d0 = 56;
	*d1 = 34;
	*d2 = 75;
	*d3 = 96;
	*d4 = 19;
	*d5 = 58;

	//设置顶点数据
	graph_set_vertex(&graph, 0, t0);
	graph_set_vertex(&graph, 1, t1);
	graph_set_vertex(&graph, 2, t2);
	graph_set_vertex(&graph, 3, t3);
	graph_set_vertex(&graph, 4, t4);

	//插入边数据
//	graph_insert_arccell(&graph, 0, 1, 15, d0);
//	graph_insert_arccell(&graph, 1, 3, 23, d1);
//	graph_insert_arccell(&graph, 1, 4, 71, d2);
//	graph_insert_arccell(&graph, 2, 0, 27, d3);
//	graph_insert_arccell(&graph, 2, 4, 36, d4);
//	graph_insert_arccell(&graph, 3, 4, 42, d5);
	//插入边数据
	graph_insert_arccell(&graph, 0, 1, 15, d0);
	graph_insert_arccell(&graph, 3, 1, 23, d1);
	graph_insert_arccell(&graph, 4, 1, 71, d2);
	graph_insert_arccell(&graph, 0, 2, 27, d3);
	graph_insert_arccell(&graph, 4, 2, 36, d4);
	graph_insert_arccell(&graph, 4, 3, 42, d5);

	/*
	 * 显示邻接表，格式如下：
	 * [顶点索引, 顶点数据] -> (边尾指向顶点的索引, 边权重, 边数据) -> (边尾指向顶点的索引, 边权重, 边数据)
	 */
	graph_visit(&graph);

	//销毁邻接表
	graph_destroy(&graph);

	return 0;
}

