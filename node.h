#ifndef __NODE_H__
#define __NODE_H__

#include "list.h"
#include "edge.h"

typedef struct edge edge_t;

typedef struct node{
    list_t edges;
    list_t list;
    list_t search_list;
    list_t circular_list;
    char data;
}node_t;

int init_node(node_t *node , char data);
void deinit_node(node_t *node);

node_t * create_node(char _data);
void destroy_node(node_t *node);

void set_edge(node_t * node, edge_t *edge);
edge_t * get_edge(node_t * node, char data);

#endif
