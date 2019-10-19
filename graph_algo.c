#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "circular_list.h"
#include "vector.h"
#include "graph_algo.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "list.h"

static int __algo_absolute_distance(graph_t *graph, char *routes)
{
    node_t *node = NULL;
    edge_t *edge = NULL;
    int length = strlen(routes);
    int sum = 0;
    int index = 0;

    for(index = 0; index < length - 1 ; index++)
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

static int algo_absolute_distance(graph_t *graph, char *routes)
{
    int sum = __algo_absolute_distance(graph, routes);
}

static int __filter_circular(edge_t *edge, circular_t *circular)
{
	node_t *node;

	LIST_FOR_EACH_ENTRY(node, &circular->circular_list, circular_list)
	{
		if(edge->destination == node)
			return -1;
	}
	return 0;
}

static int __algo_shortest_distance(node_t *origin, node_t *destination, circular_t *circular, int last_distance ,int cur_layer)
{
	edge_t *edge = NULL;
	node_t *node = NULL;
	list_t edge_list;
	int distance_tmp = 0;
	int distance = 0;
	init_list(&edge_list);
	LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
	{
		if(__filter_circular(edge, circular) < 0)
			continue;

		list_add(&edge->edge_list, &edge_list);
	}

	LIST_FOR_EACH_ENTRY(edge, &edge_list, edge_list)
	{
		distance_tmp = edge->distance + last_distance;
		if(edge->destination == destination)
			return distance_tmp;

		circular_add(circular, edge->destination);
		distance_tmp = __algo_shortest_distance(edge->destination, destination, circular, edge->distance +last_distance, cur_layer + 1);
		circular_del(circular, edge->destination);
		
		if(distance_tmp > 0)
		{
			if(distance > 0)
				distance = distance < distance_tmp ? distance : distance_tmp;
			else
				distance = distance_tmp;
		}
		
	}
	
	return distance;
}

static int algo_shortest_distance(node_t *origin, node_t *destination)
{
	int distance = 0;
	circular_t circular;
	init_circular(&circular);

	return  __algo_shortest_distance(origin, destination, &circular, distance, 0);
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

typedef struct node_distance_struct{
	node_t *node;
	int	distance;
}node_distance_t;

static int init_node_distance(node_distance_t *node_distance, node_t *node, int distance)
{
	node_distance->node = node;
	node_distance->distance = distance;
	return 1;
}

static node_distance_t *create_node_distance(node_t *node, int distance)
{
	node_distance_t *node_distance = malloc(sizeof(node_distance_t));
	if(!node_distance)
		return node_distance;

	memset(node_distance, 0, sizeof(node_distance_t));
	node_distance->node = node;
	node_distance->distance = distance;
	return node_distance;
}

static node_distance_t *create_node_distance_copy(node_distance_t *node_distance)
{
	node_distance_t *_node_distance = malloc(sizeof(node_distance_t));
	if(!_node_distance)
		return NULL;
	
	memcpy(_node_distance, node_distance, sizeof(node_distance_t));
	return _node_distance;
}

static int __search_all_routes(vector_t *vector, node_t *destination, const int distance ,int cur_layer)
{
	edge_t *edge = NULL;
	node_t *node = NULL;
	node_distance_t *node_distance = NULL;
	vector_node_t *vnode = NULL;
	vector_t node_vector;
	list_t *list;
	int counter = 0;
	int i = 0;

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
			vector_node_t *vnode_tmp = NULL;
			if(edge->destination == destination && distance > (edge->distance + node_distance->distance))
				counter++;
			init_node_distance(&_node_distance, edge->destination, edge->distance + node_distance->distance);
			if(_node_distance.distance > distance)
				continue;

			ptr_node_distance = create_node_distance_copy(&_node_distance);
			if(!ptr_node_distance)
				continue;

			vnode_tmp = create_vector_node((void*)ptr_node_distance);
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
	vector_node_t *vnode;
	node_distance_t *node_distance;
	
	node_t *node;
	edge_t *edge;

	node_distance = create_node_distance(origin, 0);
	if(!node_distance)
		return -1;

	vnode = create_vector_node((void *)node_distance);
	if(!vnode)
		return -1;

	memset(&node_vector, 0,sizeof(vector_t));
	init_vector(&node_vector);
	vector_push(&node_vector, vnode);

#if 0
	vnode = vector_pop(&node_vector);
	printf("%s:%d vnode addr = 0x%x\n",__func__,__LINE__,vnode);

	node_distance = (node_distance_t*)vnode->data;
	printf("%s:%d node_distance addr = 0x%x\n",__func__,__LINE__,node_distance);
	printf("%s:%d data[%c] ditance = %d\n",__func__,__LINE__,node_distance->node->data, node_distance->distance);
	vector_push(&node_vector, vnode);
#endif
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
