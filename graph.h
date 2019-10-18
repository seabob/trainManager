#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "list.h"
#include "node.h"

/*****************************************/
/*****************GRAPH*******************/
/*****************************************/

typedef struct graph{
   list_t nodes;
}graph_t;

int init_graph(graph_t *graph);
void deinit_graph(graph_t *graph);

void insert_node(graph_t *graph, node_t *node);
node_t * get_node(graph_t *graph, char data);

#endif
