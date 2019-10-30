#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "graph_analyzer.h"
#include "graph_algo.h"
#include "graph.h"
#include "node.h"
#include "edge.h"

int init_graph_analyzer(graph_analyzer_t *ga, graph_t *graph)
{
    ga->graph = graph;
    init_graph_algo(&ga->algo);
    return 0;
}

void deinit_graph_analyzer(graph_analyzer_t *ga)
{
    ga->graph = NULL;
    deinit_graph_algo(&ga->algo);
    return ;
}

graph_analyzer_t * create_graph_analyzer(graph_t *graph)
{
    graph_analyzer_t * ga = malloc(sizeof(graph_analyzer_t));
    if(ga == NULL)
        return ga;

    init_graph_analyzer(ga, graph);
    return ga;
}

void destroy_graph_analyzer(graph_analyzer_t *ga)
{
    deinit_graph_analyzer(ga);
    free(ga);
}

//1-5 distance-ACD
//6   routes-CC-3
//7   trips-AC-4
//8/9 short-AC short-BB
//10  allroutes-CC-30

int analyzer_graph(graph_analyzer_t *ga, char *route)
{
    char algo_cmd[16] = {0};
    char algo_route[64] = {0};
    char algo_layer[8] = {0};
    char *pcmd = route;
    char *proute = route;
    int layer = 0;
    node_t *origin = NULL;
    node_t *destination = NULL;

    pcmd = strchr(route, ' ');
    if(!pcmd)
    {
        printf("cmd field error \n");
        return -1;
    }
    strncpy(algo_cmd, route, pcmd - route);

    proute = strchr(pcmd+1, ' ');
    if(!proute)
    {
        strcpy(algo_route, pcmd + 1);
    }
    else
    {
        strncpy(algo_route, pcmd + 1, proute - pcmd - 1);
        strcpy(algo_layer, proute + 1);
	layer = atoi(algo_layer);
    }

    printf("cmd[%s], route[%s], layer[%s]\n",algo_cmd, algo_route, algo_layer);

    if(strlen(algo_route) < 2)
   	return -1;

    origin = get_node(ga->graph, algo_route[0]);
    destination = get_node(ga->graph, algo_route[1]);
	
    if(strcmp(algo_cmd, "distance") == 0)
    {
	return ga->algo.algo_absolute_distance(ga->graph, algo_route);
    }
    else if(strcmp(algo_cmd, "short") == 0)
    {

        return ga->algo.algo_shortest_distance(origin, destination);
    }
    else if(strcmp(algo_cmd, "trip") == 0)
    {
	layer = atoi(algo_layer);
	if(layer <= 0)
		return -1;
        return ga->algo.algo_trips_scheme(origin, destination, layer);
    }
    else if(strcmp(algo_cmd, "route") == 0)
    {
        layer = atoi(algo_layer);
        if(layer <= 0)
            return -1;
        
        return ga->algo.algo_routes_scheme(origin, destination, layer);
    }
    else if(strcmp(algo_cmd,"allroute") == 0)
    {
	layer = atoi(algo_layer);
	if(layer <= 0)
		return -1;
	return ga->algo.algo_all_routes(origin, destination, layer);
    }
    else if(strcmp(algo_cmd,"duration") == 0)
    {
	return ga->algo.duration_absolute_distance(ga->graph, algo_route);
    }else 
    {
        printf("UNKNOWN CMD :%s\n",algo_cmd);
    }
    return -1;
}
