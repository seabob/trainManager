#include <stdlib.h>

#include "store_node.h"
#include "vector.h"
#include "list.h"

int init_vector(vector_t *vector)
{
	if(!vector)
		return -1;

	init_list(&vector->list);
	return 0;
}

void deinit_vector(vector_t *vector)
{
	init_vector(vector);
}

void vector_push(vector_t *vector,store_node_t  *node)
{
	if(vector && node)
	{
		list_add_tail(&node->list, &vector->list);
	}
}

store_node_t* vector_pop(vector_t *vector)
{
	if(list_empty(&vector->list))
	{
		return NULL;
	}
	list_t *list = vector->list.next;
	store_node_t *node = LIST_ENTRY(list, store_node_t, list);
	list_del(list);
	return node;
}

int vector_empty(vector_t *vector)
{
	if(vector->list.next == &vector->list)
		return 1;
	return 0;
}
