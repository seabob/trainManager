#ifndef __GRAPH_ANALYZER_H__
#define __GRAPH_ANALYZER_H__

#include "graph.h"
#include "graph_algo.h"

typedef struct graph_analyzer{
    graph_t         *graph;
    graph_algo_t    algo;
}graph_analyzer_t;

int init_graph_analyzer(graph_analyzer_t * ga, graph_t *graph);
void deinit_graph_analyzer(graph_analyzer_t *ga);

int analyzer_graph(graph_analyzer_t *ga, char *route);
/*
int analyzer_absolute_distance(graph_analyzer_t *ga, const char *route);
int analyzer_shortest_route(graph_analyzer_t *ga, const char *route);
int analyzer_routes_scheme(graph_analyzer_t *ga, const char *route);
int analyzer_trips_scheme(graph_analyzer_t *ga, const char *route);
*/
#endif
