#include <stdlib.h>

#include "node.h"
#include "list.h"
#include "edge.h"


node_t * create_node(char data)
{
    node_t * node = malloc(sizeof(node_t));
    if(node == NULL)
        return NULL;

    node->data = data;
    init_list(&node->edges);

    return node;
}

void destroy_node(node_t *node)
{
    if(node)
    {
        list_del(&node->list);
        free(node);
    }
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
