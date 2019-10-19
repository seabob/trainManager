#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "train_manager.h"
#include "graph.h"
#include "route_maker.h"
#include "node.h"
#include "file_reader.h"


int init_train_manager(train_manager_t *tm, const char *testcase_file)
{
    init_graph(&tm->graph);
    init_route_maker(&tm->route_maker, &tm->graph);
    init_graph_analyzer(&tm->graph_analyzer, &tm->graph);

    if(testcase_file == NULL)
        init_file_reader(&tm->reader, TEST_CASE_FILE);
    else
        init_file_reader(&tm->reader, testcase_file);
    return 0;
}

void deinit_train_manager(train_manager_t *tm)
{
     deinit_graph_analyzer(&tm->graph_analyzer);
     deinit_route_maker(&tm->route_maker);
     deinit_file_reader(&tm->reader);
     deinit_graph(&tm->graph);
}

train_manager_t * create_train_manager(const char * testcase_file)
{
    train_manager_t * tm = malloc(sizeof(train_manager_t));
    if(!tm)
        return tm;
    
    memset(tm, 0, sizeof(train_manager_t));
    init_train_manager(tm, testcase_file);
    return tm;
}

void destroy_train_manager(train_manager_t *tm)
{
    deinit_train_manager(tm);
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

int get_calculate(train_manager_t *tm, char *path)
{
    return analyzer_graph(&tm->graph_analyzer,path);
}

int get_testcase(train_manager_t *tm, char *test_case, size_t length)
{
    return get_test_case(&tm->reader, test_case, length);
}


//Show all route and relation
void print_routes(train_manager_t *train_manager)
{
    node_t *node = NULL;
    node_t *tmp_node = NULL;
    edge_t *edge = NULL;
    edge_t *tmp_edge = NULL;
    printf("\n----------graph struction----------\n");
    LIST_FOR_EACH_ENTRY_PREV_SAFE(node, tmp_node, &train_manager->graph.nodes,list)
    {
        printf("origin %c:\n",node->data);
        LIST_FOR_EACH_ENTRY_PREV_SAFE(edge, tmp_edge, &node->edges, list)
        {
            printf(" -%c- destination [%d] \n",edge->destination->data, edge->distance);
        }
    }
    printf("\n-----------------------------------\n");
}
