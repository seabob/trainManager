#include <stdlib.h>

#include "graph.h"
#include "list.h"
#include "node.h"

int init_graph(graph_t *graph)
{
    if(graph)
    {
        init_list(&graph->nodes);
	return 0;
    }
    return -1;
}

void deinit_graph(graph_t *graph)
{
    init_graph(graph);
}

void insert_node(graph_t *graph, node_t * node)
{
    if(graph && node)
    {
        list_add(&node->list, &graph->nodes);
    }
}

node_t * get_node(graph_t *graph, char data)
{
    node_t *pos = NULL;
    node_t *tmp = NULL;

    if(graph)
    {
        LIST_FOR_EACH_ENTRY_SAFE(pos, tmp, &graph->nodes, list)
        {
            if(pos->data == data)
            {
                return pos;
            }
        }
    }
    return NULL;
}
