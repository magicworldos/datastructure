#include <stdio.h>
#include "graph.h"

int main(int argc, char **args)
{
	s_graph graph;
	graph_init(&graph, 5);

	for (int i = 0; i < 5; i++)
	{
		graph_set_vertex(&graph, i, i * 2 + 3);
	}

	graph_set_arccell(&graph, 0, 0, 11);
	graph_set_arccell(&graph, 0, 3, 2);
	graph_set_arccell(&graph, 1, 0, 37);
	graph_set_arccell(&graph, 4, 1, 43);
	graph_set_arccell(&graph, 2, 2, 12);
	graph_set_arccell(&graph, 3, 4, 76);
	graph_set_arccell(&graph, 2, 0, 12);
	graph_set_arccell(&graph, 2, 4, 18);
	graph_set_arccell(&graph, 3, 1, 13);

	graph_display(&graph);

	graph_destroy(&graph);

	return 0;
}

