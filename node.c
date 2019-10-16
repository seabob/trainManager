#include <stdlib.h>

#include "node.h"
#include "list.h"
#include "edge.h"

int init_node(node_t *node, char data)
{
    if(!node)
        return -1;

    node->data = data;
    init_list(&node->edges);
    return 0;
}

void deinit_node(node_t *node)
{
    if(!node)
        return ;

    init_node(node, 0);
}


node_t * create_node(char data)
{
    node_t * node = malloc(sizeof(node_t));
    if(!node)
        return NULL;

    init_node(node, data);

    return node;
}

void destroy_node(node_t *node)
{
    if(!node)
        return ;

    deinit_node(node);
    free(node);
}

void set_edge(node_t *node, edge_t *edge)
{
    if(node && edge)
    {
        list_add(&edge->list, &node->edges);
    }
}

edge_t * get_edge(node_t *node, char data)
{
    edge_t *pos = NULL;
    edge_t *tmp = NULL;

    if(node)
    {
        LIST_FOR_EACH_ENTRY_SAFE(pos, tmp, &node->edges, list)
        {
            if(pos->destination->data == data)
                return pos;
        }
    }

    return NULL;
}
