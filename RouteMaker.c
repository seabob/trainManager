#include <malloc.h>

#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include "Route.h"
#include "RouteMaker.h"

int init_route_maker(route_maker_t *route_maker, graph_t *graph)
{
    route_maker->graph = graph;
    return 0;
}

void destroy_route_maker(route_maker_t *route_maker)
{
    route_maker->graph = NULL;
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
