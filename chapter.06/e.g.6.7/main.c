#include <stdio.h>
#include "graph.h"

int main(int argc, char **args)
{
	s_graph graph;
	graph_init(&graph, 6);

	for (int i = 0; i < 6; i++)
	{
		graph_set_vertex(&graph, i, i);
	}

	graph_set_arccell(&graph, 0, 2, 10);
	graph_set_arccell(&graph, 0, 4, 30);
	graph_set_arccell(&graph, 0, 5, 100);
	graph_set_arccell(&graph, 1, 2, 5);
	graph_set_arccell(&graph, 2, 3, 50);
	graph_set_arccell(&graph, 3, 5, 10);
	graph_set_arccell(&graph, 4, 3, 20);
	graph_set_arccell(&graph, 4, 5, 60);

	graph_display(&graph);

	graph_shortest_path(&graph);

	graph_destroy(&graph);

	return 0;
}

