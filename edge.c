#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "edge.h"
#include "list.h"

edge_t * create_edge(node_t *destination, int distance)
{
    edge_t *edge = malloc(sizeof(edge_t));
    if(edge == NULL)
        return NULL;

    memset(edge, 0, sizeof(edge));
    init_list(&edge->list);
    edge->destination = destination;
    edge->distance = distance;
    return edge;
}

void destroy_edge(edge_t *edge)
{
    if(edge != NULL)
    {
        list_del(&edge->list);
        free(edge);
    }
}
