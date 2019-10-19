#include <stdlib.h>
#include <string.h>
#include "store_node.h"

int init_store_node(store_node_t *node, void * data)
{
   	if(node)
	{
		node->data = data;
		init_list(&node->list);
		return 0;
	}
}
void deinit_store_node(store_node_t *node)
{
    if(node)
	{
		list_del(&node->list);
	}
}

store_node_t * create_store_node(void *data)
{
    store_node_t *node = malloc(sizeof(store_node_t));
	if(!node)
		return NULL;
	init_store_node(node, data);
	
	return node;
}
void destroy_store_node(store_node_t *node)
{
	if(!node)
		return ;
	deinit_store_node(node);
	free(node);
}
