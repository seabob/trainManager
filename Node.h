#ifndef __NODE_H__
#define __NODE_H__

#include "List.h"
#include "Edge.h"

typedef struct edge edge_t;

typedef struct node{
    list_t edges;
    list_t list;
    char data;
}node_t;

node_t * create_node(char _data);
void destroy_node(node_t *node);

void set_edge(node_t * node, edge_t *edge);
edge_t * get_edge(node_t * node, char data);

#endif
