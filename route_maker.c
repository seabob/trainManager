#include <stdlib.h>

#include "list.h"
#include "edge.h"
#include "node.h"
#include "graph.h"
#include "route.h"
#include "route_maker.h"

int init_route_maker(route_maker_t *route_maker, graph_t *graph)
{
    route_maker->graph = graph;
    return 0;
}

void deinit_route_maker(route_maker_t *route_maker)
{
    node_t *node = NULL;
    node_t *node_tmp = NULL;
    edge_t *edge = NULL;
    edge_t *edge_tmp = NULL;

    LIST_FOR_EACH_ENTRY_SAFE(node, node_tmp, &route_maker->graph->nodes,list)
    {
	LIST_FOR_EACH_ENTRY_SAFE(edge, edge_tmp, &node->edges, list)
        {
		destroy_edge(edge);
        }
        destroy_node(node);
    }

    route_maker->graph = NULL;
}
void destroy_route_maker(route_maker_t *route_maker)
{
    deinit_route_maker(route_maker);
}

node_t *check_or_create(route_maker_t * route_maker, char data)
{
    node_t *node = NULL;

    if(route_maker)
    {
        node = get_node(route_maker->graph, data);
    }

    if(node == NULL)
    {
        node = create_node(data);
        if(node)
        {
            insert_node(route_maker->graph, node);
        }
    }
    return node;
}

int add_route(route_maker_t *route_maker, route_t * route)
{
    edge_t *edge = NULL;
    node_t *origin = check_or_create(route_maker, route->origin);
    node_t *destination = check_or_create(route_maker, route->destination);

    if(origin && destination)
    {
        edge = create_edge(destination, route->distance);
        set_edge(origin, edge);
        return 0;
    }
    return -1;
}
