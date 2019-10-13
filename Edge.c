#include <malloc.h>

#include "Node.h"
#include "Edge.h"
#include "List.h"

edge_t * create_edge(node_t *destination, int distance)
{
    edge_t *edge = malloc(sizeof(node_t));
    if(edge == NULL)
        return NULL;

    init_list(&edge->list);
    edge->destination = destination;
    edge->distance = distance;
    return edge;
}

void destroy_edge(edge_t *edge)
{
    if(edge != NULL)
        free(edge);
}
