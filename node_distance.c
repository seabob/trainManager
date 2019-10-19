#include <stdlib.h>
#include <string.h>

#include "node.h"

typedef struct node_distance_struct{
        node_t *node;
        int     distance;
}node_distance_t;

int init_node_distance(node_distance_t *node_distance, node_t *node, int distance)
{
        node_distance->node = node;
        node_distance->distance = distance;
        return 1;
}

node_distance_t *create_node_distance(node_t *node, int distance)
{
        node_distance_t *node_distance = malloc(sizeof(node_distance_t));
        if(!node_distance)
                return node_distance;

        memset(node_distance, 0, sizeof(node_distance_t));
        node_distance->node = node;
        node_distance->distance = distance;
        return node_distance;
}

node_distance_t *create_node_distance_copy(node_distance_t *node_distance)
{
        node_distance_t *_node_distance = malloc(sizeof(node_distance_t));
        if(!_node_distance)
                return NULL;

        memcpy(_node_distance, node_distance, sizeof(node_distance_t));
        return _node_distance;
}

void deinit_node_distance(node_distance_t *node_distance)
{
	if(!node_distance)
		return ;

	node_distance->node = NULL;
	node_distance->distance = 0;
}

void destroy_node_distance(node_distance_t *node_distance)
{
	if(!node_distance)
		return ;

	deinit_node_distance(node_distance);
	free(node_distance);
}
