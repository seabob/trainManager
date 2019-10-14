#ifndef __GRAPH_ANALYZER_H__
#define __GRAPH_ANALYZER_H__

#include "graph.h"

typedef struct graph_analyzer{
    graph_t *graph;
}graph_analyzer_t;

int init_graph_analyzer(graph_analyzer_t * ga, graph_t *graph);
void deinit_graph_analyzer(graph_analyzer_t *ga);
int calculate_distance(graph_analyzer_t *ga, const char *route);

#endif
