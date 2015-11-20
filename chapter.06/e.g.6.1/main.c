#include <stdio.h>
#include "graph.h"

int main(int argc, char **args)
{
	s_graph graph;
	graph_init(&graph, 5);

	for (int i = 0; i < 5; i++)
	{
		graph_set_vertex(&graph, i, i);
	}

	graph_set_arccell(&graph, 0, 1, 15);
	graph_set_arccell(&graph, 1, 4, 71);
	graph_set_arccell(&graph, 1, 3, 23);
	graph_set_arccell(&graph, 3, 4, 42);
	graph_set_arccell(&graph, 2, 4, 36);
	graph_set_arccell(&graph, 2, 0, 27);
	graph_set_arccell(&graph, 3, 3, 61);
	graph_set_arccell(&graph, 2, 1, 92);

	graph_display(&graph);

	graph_destroy(&graph);

	return 0;
}

