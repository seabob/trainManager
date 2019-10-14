#ifndef __ROUTE_MAKER_H__
#define __ROUTE_MAKER_H__

#include "graph.h"
#include "route.h"
#include "node.h"

typedef struct route_maker{
    graph_t *graph;
}route_maker_t;

int init_route_maker(route_maker_t *route_maker, graph_t *graph);
void deinit_route_maker(route_maker_t *route_maker);
route_maker_t * create_route_maker(graph_t *graph);
void destroy_route_maker(route_maker_t *route_maker);

int add_route(route_maker_t *route_maker, route_t *route);
node_t *check_or_create(route_maker_t *route_maker, char data);

#endif
