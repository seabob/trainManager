#ifndef __STORE_NODE_H__
#define __STORE_NODE_H__

#include "list.h"

typedef struct store_node_list{
	void	*data;
	list_t	list;
}store_node_t;

int init_store_node(store_node_t *node, void * data);
void deinit_store_node(store_node_t *node);

store_node_t * create_store_node(void *data);
void destroy_store_node(store_node_t *node);

#endif
