#ifndef __GRAPH_ALGO_H__
#define __GRAPH_ALGO_H__

#include "graph.h"
#include "node.h"

#define ALGO_NAME_LEN   64

typedef struct graph_algo{
//    char    algo_name[ALGO_NAME_LEN];
    int     (*algo_absolute_distance)(graph_t *graph, const char *route);
    int     (*duration_absolute_distance)(graph_t *graph, const char *route);
    int     (*algo_shortest_distance)(node_t *origin ,node_t *destination);
    int     (*algo_routes_scheme)(node_t *origin, node_t *destination, const int layer);
    int     (*algo_trips_scheme)(node_t *origin, node_t *destination, const int layer);
    int     (*algo_all_routes)(node_t *origin, node_t *destination, const int layer);
}graph_algo_t;

int init_graph_algo(graph_algo_t *algo);
void deinit_graph_algo(graph_algo_t *algo);

#endif
