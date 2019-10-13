#ifndef __TRAIN_MANAGER_H__
#define __TRAIN_MANAGER_H__

#include "Graph.h"
#include "RouteMaker.h"
#include "GraphAnalyzer.h"

typedef struct train_manager{
    graph_t             graph;
    route_maker_t       route_maker;
    graph_analyzer_t    graph_analyzer;
}train_manager_t;


int init_train_manager(train_manager_t * train_manager);

train_manager_t *create_train_manager(void);
void destroy_train_manager(train_manager_t *train_manager);

void insert_route(train_manager_t *train_manager, const char * route);
int get_distance(train_manager_t *train_manager, const char *path);




#endif
