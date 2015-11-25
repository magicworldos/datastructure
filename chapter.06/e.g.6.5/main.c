#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void visit_int(int *i)
{
	if (i != null)
	{
		printf("%d ", *i);
	}
}

int main(int argc, char **args)
{
	//邻接表
	s_graph graph;
	graph_init(&graph, 13, &visit_int, &visit_int);

	//顶点数据项
	int *t0 = (int *) malloc(sizeof(int));
	int *t1 = (int *) malloc(sizeof(int));
	int *t2 = (int *) malloc(sizeof(int));
	int *t3 = (int *) malloc(sizeof(int));
	int *t4 = (int *) malloc(sizeof(int));
	int *t5 = (int *) malloc(sizeof(int));
	int *t6 = (int *) malloc(sizeof(int));
	int *t7 = (int *) malloc(sizeof(int));
	int *t8 = (int *) malloc(sizeof(int));
	int *t9 = (int *) malloc(sizeof(int));
	int *t10 = (int *) malloc(sizeof(int));
	int *t11 = (int *) malloc(sizeof(int));
	int *t12 = (int *) malloc(sizeof(int));
	//顶点数据
	*t0 = 0;
	*t1 = 1;
	*t2 = 2;
	*t3 = 3;
	*t4 = 4;
	*t5 = 5;
	*t6 = 6;
	*t7 = 7;
	*t8 = 8;
	*t9 = 9;
	*t10 = 10;
	*t11 = 11;
	*t12 = 12;

	//设置顶点数据
	graph_set_vertex(&graph, 0, t0);
	graph_set_vertex(&graph, 1, t1);
	graph_set_vertex(&graph, 2, t2);
	graph_set_vertex(&graph, 3, t3);
	graph_set_vertex(&graph, 4, t4);
	graph_set_vertex(&graph, 5, t5);
	graph_set_vertex(&graph, 6, t6);
	graph_set_vertex(&graph, 7, t7);
	graph_set_vertex(&graph, 8, t8);
	graph_set_vertex(&graph, 9, t9);
	graph_set_vertex(&graph, 10, t10);
	graph_set_vertex(&graph, 11, t11);
	graph_set_vertex(&graph, 12, t12);

	//插入边数据
	graph_insert_arccell(&graph, 0, 1, 0, null);
	graph_insert_arccell(&graph, 0, 2, 0, null);
	graph_insert_arccell(&graph, 1, 3, 0, null);
	graph_insert_arccell(&graph, 1, 4, 0, null);
	graph_insert_arccell(&graph, 2, 5, 0, null);
	graph_insert_arccell(&graph, 2, 6, 0, null);
	graph_insert_arccell(&graph, 3, 4, 0, null);
	graph_insert_arccell(&graph, 3, 7, 0, null);
	graph_insert_arccell(&graph, 5, 8, 0, null);
	graph_insert_arccell(&graph, 6, 9, 0, null);
	graph_insert_arccell(&graph, 6, 10, 0, null);
	graph_insert_arccell(&graph, 8, 11, 0, null);
	graph_insert_arccell(&graph, 10, 11, 0, null);
	graph_insert_arccell(&graph, 10, 12, 0, null);

	//显示顶点和边的关系
	graph_visit(&graph);

	//深度优先遍历图
	graph_depth_first_search(&graph);

	//销毁邻接表
	graph_destroy(&graph);

	return 0;
}

