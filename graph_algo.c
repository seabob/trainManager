#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "circular_list.h"
#include "search_list.h"
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
	printf("data = %c\n", origin->data);
	LIST_FOR_EACH_ENTRY(edge, &origin->edges, list)
	{
		if(__filter_circular(edge, circular) < 0)
			continue;
	printf("edge data = %c\n", edge->destination->data);

		list_add(&edge->edge_list, &edge_list);
	}

	LIST_FOR_EACH_ENTRY(edge, &edge_list, edge_list)
	{
		distance_tmp = edge->distance + last_distance;
		printf("%d -> %c\n", edge->distance,edge->destination->data );
		if(edge->destination == destination)
		{
			printf("distanceTMP[%c] = %d\n",edge->destination->data,distance_tmp);
			return distance_tmp;
		}

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
	printf("%d->[%c]tmp = %d\n", distance,edge->destination->data,distance_tmp);
		
	}
	
	printf("distance[%c] = %d\n", edge->destination->data,distance);
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

static int __search_all_routes(search_t *search, node_t *destination, const int layer ,int cur_layer)
{
	edge_t *edge = NULL;
	node_t *node = NULL;
	search_t *se = malloc(sizeof(search_t));
	list_t *list;
	int counter = 0;
	int i = 0;
	memset(se,0,sizeof(search_t));
	init_search(se);

	printf("cur_layer = %d\n",cur_layer);
	if(layer <= cur_layer)
		return counter;

	LIST_FOR_EACH_ENTRY(node, &search->search_list, search_list)
	{
		list_t *head = &node->edges;
		list_t *cur = head->next;
		while(cur != head)
		{
			edge = __CONTAINER_OF(cur, edge, list);
			if(edge)
			{
				node = edge->destination;
				printf("node->data = %c, edge->distance = %d\n",node->data, edge->distance);
//				circular_add(&_search, node);
				search_add(se, node);
//				printf("%s:%d\n",__func__,__LINE__);
			}
			cur = cur->next;
		}
	}
/*
	LIST_FOR_EACH_ENTRY(node, &search->circular_list, circular_list)
	{
		printf("node data = %c, i = %d\n",node->data,i);
		i = 0;
//		for(list = node->edges.next; list != &node->edges ; list = list->next)
		LIST_FOR_EACH_ENTRY(edge, &node->edges, list)
		{
			i++;
//			if(edge->destination == destination)
//			{
//				printf("data = %c\n",edge->destination);
//				counter++;
//			}
			search_add(&_search, edge->destination);
		}
	}
*/

//	counter += __search_all_routes(&_search, destination, layer, cur_layer+1);
	return counter ;
}


static int algo_all_routes(node_t *origin, node_t *destination, const int layer)
{
	int counter = 0;
	search_t search;
	node_t *node;
	edge_t *edge;
	memset(&search, 0,sizeof(search_t));
	init_search(&search);
	search_add(&search, origin);

	counter += __search_all_routes(&search, destination, layer, 0);

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
