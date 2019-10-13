#ifndef __EDGE_H__
#define __EDGE_H__

#include "List.h"
#include "Node.h"

typedef struct node node_t;

typedef struct edge{
    list_t list;
    node_t *destination;
    int distance;
}edge_t;

edge_t * create_edge(node_t *destination, int distance);
void destroy_edge(edge_t * edge);

#endif