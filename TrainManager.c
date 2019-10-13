#include <stdlib.h>
#include <string.h>

#include "TrainManager.h"
#include "Graph.h"
#include "RouteMaker.h"
#include "Node.h"


int init_train_manager(train_manager_t *tm)
{
    init_graph(&tm->graph);
    init_route_maker(&tm->route_maker, &tm->graph);
    init_graph_analyzer(&tm->graph_analyzer, &tm->graph);
    return 0;
}

train_manager_t * create_train_manager(void)
{
    train_manager_t * tm = malloc(sizeof(train_manager_t));
    if(!tm)
        return tm;
    
    memset(tm, 0, sizeof(train_manager_t));
    init_train_manager(tm);
    return tm;
}

void destroy_train_manager(train_manager_t *tm)
{
    if(tm)
        free(tm);
}

void insert_route(train_manager_t *tm, const char *raw_route)
{
    route_t route;
    memset(&route,0,sizeof(route_t));

    init_route(&route, raw_route);
    add_route(&tm->route_maker, &route);
}

int get_distance(train_manager_t *tm, const char *path)
{
    return calculate_distance(&tm->graph_analyzer,path);
}
