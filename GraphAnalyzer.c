#include <stdlib.h>
#include <string.h>

#include "GraphAnalyzer.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

int init_graph_analyzer(graph_analyzer_t *ga, graph_t *graph)
{
    ga->graph = graph;
    return 0;
}

graph_analyzer_t * create_graph_analyzer(graph_t *graph)
{
    graph_analyzer_t * ga = malloc(sizeof(graph_analyzer_t));
    if(ga == NULL)
        return ga;

    ga->graph = graph;
    return ga;
}

void destroy_graph_analyzer(graph_analyzer_t *ga)
{
    destroy_graph(ga->graph);
    free(ga);
}

int calculate_distance(graph_analyzer_t *ga, const char *route)
{
    int sum = 0;
    int index = 0;
    int length = strlen(route);
    node_t *current = NULL;
    edge_t *next = NULL;


    for(index = 0; index < length - 2; index += 2)
    {
         current = get_node(ga->graph, route[index]);
         next = get_edge(current, route[index+2]);
         if(next)
            sum += next->distance;
        else
            return -1;
    }

    return sum;
}
