#include <stdlib.h>
#include <string.h>

#include "graph_analyzer.h"
#include "graph_algo.h:"
#include "graph.h"
#include "node.h"
#include "edge.h"

int init_graph_analyzer(graph_analyzer_t *ga, graph_t *graph)
{
    ga->graph = graph;
    init_graph_algo(ga->algo);
    return 0;
}

void deinit_graph_analyzer(graph_analyzer_t *ga)
{
    ga->graph = NULL;
    deinit_graph_algo(ga->algo);
    return ;
}

graph_analyzer_t * create_graph_analyzer(graph_t *graph)
{
    graph_analyzer_t * ga = malloc(sizeof(graph_analyzer_t));
    if(ga == NULL)
        return ga;

    init_graph_analyzer(ga, graph);
    return ga;
}

void destroy_graph_analyzer(graph_analyzer_t *ga)
{
    deinit_graph_analyzer(ga);
    free(ga);
}

