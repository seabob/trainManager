#include <stdlib.h>
#include <string.h>
#include "graph_algo.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "list.h"

static int algo_absolute_distance(graph_t *graph, const char *routes)
{
    node_t *current = NULL;
    edge_t *next = NULL;
    int sum = 0;
    size_t lenght = strlen(routes);
    int index = 0;


    for(index = 0; index < length; index++)
    {
        current = get_node(graph, routes[index]);
        next = get_edge(graph, routes[index+1]);
        if(next)
            sum += next->distance;
        else
            return -1;
    }

    return sum;
}

typedef struct __node_list{
    node_t      *node;
    list_t      list;
}node_list_t;

static int init_node_list(node_list_t *head, node_t *node)
{
    if(!head)
        return -1;

    memset(head, 0, sizeof(node_list_t));
    list_init(&head->list);
    head->node = node;
    return 0;
}

static void deinit_node_list(node_list_t *head)
{
    init_node_list(head);
    list_del(&head->list);
}

static node_list_t * create_node_list(node_t *node)
{
    node_list_t *lnode = malloc(sizeof(node_list_t));
    if(!lnode)
        return NULL;
    
    init_node_list(lnode, node);
    return lnode;
}

static void destory_node_list(node_list_t *lnode)
{
    if(!lnode)
        return;
    deinit_node_list(lnode);
    free(lnode);
}

static void add_node_list(node_list_t *head, node_list_t *node)
{
    if(head && node)
        list_add(&node->list, &head->list);
}

//breadth first
static int __algo_shortest_distance(node_t *origin, node_t *destination, int cur_layer)
{
    node_list_t lnodes;
    node_list_t *lnode_pos = NULL;
    edge_t *edge = NULL;
    int ret = 0;

    if(list_empty(&origin->edges))
        return ret;

    init_node_list(&lnodes, NULL);

    LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
    {
        node_list_t *lnode = NULL;
        if(edge->destination == destination)
        {
            node_list_t *lnode_tmp = NULL;
            LIST_FOR_EACH_ENTRY_SAFE(lnode, lnode_tmp, &lnodes.list, list)
            {
                if(lnode)
                {
                    destroy_node_list(lnode);
                }
            }
            return cur_layer;
        }
        lnode = create_node_list(edge->destination);
        if(lnode)
            add_node_list(&lnodes, lnode);
    }

    do{
        node_list_t *lnode_tmp = NULL;
        LIST_FOR_EACH_ENTRY_SAFE(lnode_pos, lnode_tmp, &lnodes.list, list)
        {
            list_del(&lnode_pos->list);
            ret = __algo_shortest_distance(lnode_pos->node, destination, 1 + cur_layer);
            destroy_node_list(lnode_pos);
            if(ret > 0)
                return ret;
        }
    while(0);

    return ret;
}

static int algo_shortest_distance(node_t *origin, node_t *destination)
{
    int cur_layer = __algo_shortest_distance(origin, destination, 0);
}
//depth first
static int __search_routes_scheme(node_t *origin, node_t *destination, const int layer,
                                            int cur_layer)
{
    node_t *node = NULL;
    edge_t *edge = NULL;
    int counter = 0;

    if(cur_layer > layer)
        return counter;

    if(list_empty(&origin->edges))
        return counter;

    LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
    {
        if(edge->destination == destination)
            counter++;

        node = edge->destination;
        counter += __search_route_plans(edge->destination, destination,layer, 1 + cur_layer);
    }
    return counter;
}

static int algo_routes_scheme(node_t *origin, node_t *destination, const int layer)
{
    int counter = 0;
    int cur_layer = 0;
    counter += __search_route_plans(origin, destination, layer, cur_layer);
    if(counter == 0)
        return -1;
    return counter;
}

//depth first
static int __search_trips_scheme(node_t *origin, node_t *destination, 
                                    const int layer, int cur_layer)
{
    edge_t *edge = NULL;
    int counter = 0;

    if(list_empty(&origin->edges))
        return 0;

    if(layer == cur_layer)
    {
        LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
        {
            if(edge->destination = destination)
            {
                counter++;
            }
        }
        return counter;
    }
    else if(layer < cur_layer)
    {
        LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
        {
            counter += __algo_travel_plans(edge->destination, destination, layer, cur_layer + 1);
        }
    }
    
    return counter;
}
static int algo_trips_scheme(node_t *origin, node_t *destination, const int layer)
{
    int cur_layer = 0;
    int counter = __search_travel_scheme(origin, destination, layer, cur_layer);

    if(counter == 0)
        return -1;

    return counter;
}

static graph_algo_t __defalut_graph_algo = {
    .algo_name = "default_algo",
    .algo_absolute_distance = algo_absolute_distance,
    .algo_shortest_distance = algo_shortest_distance,
    .algo_routes_scheme = algo_routes_scheme,
    .algo_trips_scheme = algo_trips_scheme,
};

int init_graph_algo(graph_algo_t *algo)
{
    algo = &__default_graph_algo;
    return 0;
}

void dinit_graph_algo(graph_algo_t *algo)
{
    memset(algo, 0, sizeof(graph_algo_t));
}