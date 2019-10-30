#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "stack.h"
#include "node_distance.h"
#include "graph_algo.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "list.h"

static int __algo_absolute_distance(graph_t *graph, const char *routes)
{
    node_t *node = NULL;
    edge_t *edge = NULL;
    int length = strlen(routes);
    int sum = 0;
    int index = 0;

    for(index = 0; index < length-1; index++)
    {
    	node = get_node(graph, routes[index]);
	edge = get_edge(node, routes[index+1]);
	if(edge)
	{
	    sum += edge->distance;
	}else
	{
	    return -1;
	}
    }

    return sum;
}

static int algo_absolute_distance(graph_t *graph, const char *routes)
{
    return __algo_absolute_distance(graph, routes);
}

static int duration_absolute_distance(graph_t *graph, const char *routes)
{
    int ret = 0;
    int sum = 0;
    int index = 0;
    int length = strlen(routes);

    sum += (length - 2) * 2;

    ret = __algo_absolute_distance(graph, routes);
    if(ret >= 0)
	return (sum + ret);
    return -1;
}

static int __algo_shortest_distance(node_t *origin, node_t *destination, stack_t *stack, int last_distance, int cur_layer)
{
	edge_t *edge = NULL;
	node_t *node = NULL;
	store_node_t store_node;
	store_node_t *vnode;
	int distance = 0;
	int distance_tmp = 0;

	LIST_FOR_EACH_ENTRY(vnode, &stack->list, list)
	{
		node = (node_t*)vnode->data;
		if(node == origin)
			return 0;
	}

	init_store_node(&store_node, (void*)origin);	
	stack_push(stack, &store_node);
	LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)	
	{
		if(edge->destination == destination)
		{
			distance = edge->distance + last_distance;
			continue;
		}
		
		distance_tmp = __algo_shortest_distance(edge->destination, destination, stack, last_distance + edge->distance, cur_layer + 1);
		if(distance_tmp > 0)
		{
			if(distance > 0)
				distance = distance < distance_tmp ? distance : distance_tmp;
			else
				distance = distance_tmp;
		}
	}
	stack_pop(stack);
	return distance;
}

static int algo_shortest_distance(node_t *origin, node_t *destination)
{
	stack_t stack;
	init_stack(&stack);

	return  __algo_shortest_distance(origin, destination, &stack, 0, 0);
}

static int __search_routes_scheme(node_t *origin, node_t *destination,const int layer, int cur_layer)
{
	int count = 0;
	edge_t *edge = NULL;

	if(cur_layer >= layer)
		return count;

	LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
	{
		count += __search_routes_scheme(edge->destination, destination, layer, cur_layer + 1);
		if(edge->destination == destination)
		{
			count += 1;
		}
	}
	return count;
}


static int algo_routes_scheme(node_t *origin, node_t *destination, const int layer)
{
    int cur_layer = 0;
    int counter = 0;

    counter += __search_routes_scheme(origin, destination, layer, cur_layer);
    if(counter <= 0)
        return -1;
    return counter;
}

//depth first
static int __search_trips_scheme(node_t *origin, node_t *destination,const int layer, int cur_layer)
{
	int count = 0;
	edge_t *edge = NULL;
	if(cur_layer > layer)
		return count;

	LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
	{
		count += __search_trips_scheme(edge->destination, destination, layer, cur_layer + 1);
		if(cur_layer == layer)
			if(edge->destination == destination)
				count += 1;
	}
	return count;
}

static int algo_trips_scheme(node_t *origin, node_t *destination, const int layer)
{
    int cur_layer = 0;
    int counter = __search_trips_scheme(origin, destination, layer, cur_layer);

    if(counter == 0)
        return -1;

    return counter;
}

static int __search_all_routes(vector_t *vector, node_t *destination, const int distance ,int cur_layer)
{
	edge_t *edge = NULL;
	node_t *node = NULL;
	node_distance_t *node_distance = NULL;
	store_node_t *vnode = NULL;
	vector_t node_vector;
	int counter = 0;

	memset(&node_vector, 0 ,sizeof(vector_t));
	init_vector(&node_vector);

	if(vector_empty(vector))
		return counter;

	while(!vector_empty(vector))
	{
		vnode = vector_pop(vector);
		if(vnode == NULL)
			continue;
		
		node_distance = (node_distance_t*)vnode->data;
		if(node_distance->distance >= distance)
		{
			free(node_distance);
			free(vnode);
			continue;
		}

		node = node_distance->node;
		LIST_FOR_EACH_ENTRY(edge, &node->edges, list)
		{
			node_distance_t _node_distance;
			node_distance_t *ptr_node_distance = NULL;
			store_node_t *vnode_tmp = NULL;
			if(edge->destination == destination && distance > (edge->distance + node_distance->distance))
				counter++;
			init_node_distance(&_node_distance, edge->destination, edge->distance + node_distance->distance);
			if(_node_distance.distance > distance)
				continue;

			ptr_node_distance = create_node_distance_copy(&_node_distance);
			if(!ptr_node_distance)
				continue;

			vnode_tmp = create_store_node((void*)ptr_node_distance);
			if(!vnode_tmp)
				continue;

			vector_push(&node_vector, vnode_tmp);
		}
		free(node_distance);
		free(vnode);
	}

	counter += __search_all_routes(&node_vector, destination, distance, cur_layer+1);
	return counter ;
}


static int algo_all_routes(node_t *origin, node_t *destination, const int distance)
{
	int counter = 0;
	vector_t node_vector;
	store_node_t *vnode;
	node_distance_t *node_distance;

	node_distance = create_node_distance(origin, 0);
	if(!node_distance)
		return -1;

	vnode = create_store_node((void *)node_distance);
	if(!vnode)
		return -1;

	memset(&node_vector, 0,sizeof(vector_t));
	init_vector(&node_vector);
	vector_push(&node_vector, vnode);

	counter += __search_all_routes(&node_vector, destination, distance, 0);

	if(counter <= 0)
		return -1;

	return counter;
}


static graph_algo_t __default_graph_algo = {
    .algo_absolute_distance = algo_absolute_distance,
    .algo_shortest_distance = algo_shortest_distance,
    .algo_routes_scheme = algo_routes_scheme,
    .algo_trips_scheme = algo_trips_scheme,
    .algo_all_routes = algo_all_routes,
    .duration_absolute_distance = duration_absolute_distance,
};

int init_graph_algo(graph_algo_t *algo)
{
    memset(algo, 0, sizeof(graph_algo_t));
    memcpy(algo, &__default_graph_algo, sizeof(graph_algo_t));
    return 0;
}

void deinit_graph_algo(graph_algo_t *algo)
{
    memset(algo, 0, sizeof(graph_algo_t));
}
