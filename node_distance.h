#ifndef __NODE_DISTANCE_H__
#define __NODE_DISTANCE_H__

#include "node.h"
typedef struct node_distance_struct{
        node_t *node;
        int     distance;
}node_distance_t;

int init_node_distance(node_distance_t *node_distance, node_t *node, int distance);
node_distance_t *create_node_distance(node_t *node, int distance);
node_distance_t *create_node_distance_copy(node_distance_t *node_distance);

void deinit_node_distance(node_distance_t *node_distance);
void destroy_node_distance(node_distance_t *node_distance);


#endif
