#ifndef __EDGE_H__
#define __EDGE_H__

#include "list.h"
#include "node.h"

typedef struct node node_t;

//Graph's Edge
typedef struct edge{
    list_t edge_list;
    list_t list;
    node_t *destination;
    int distance;
}edge_t;

//Dynamically apply for memory
edge_t * create_edge(node_t *destination, int distance);
void destroy_edge(edge_t * edge);

#endif
