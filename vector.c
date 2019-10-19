#include <stdlib.h>

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

void vector_push(vector_t *vector,vector_node_t  *node)
{
	if(vector && node)
	{
		list_add_tail(&node->list, &vector->list);
	}
}

vector_node_t* vector_pop(vector_t *vector)
{
	if(list_empty(&vector->list))
	{
		printf("%s:%d list_empty1\n",__func__,__LINE__);
		return NULL;
	}
	list_t *list = vector->list.next;
	vector_node_t *node = LIST_ENTRY(list, vector_node_t, list);
	printf("%s:%d vector_node addr = 0x%x\n",__func__,__LINE__,node);
	list_del(list);
	return node;
}

int init_vector_node(vector_node_t *node, void *data)
{
	if(node)
	{
		node->data = data;
		init_list(&node->list);
		return 0;
	}
	return -1;
}

void deinit_vector_node(vector_node_t *node)
{
	if(node)
	{
		list_del(&node->list);
	}
}

vector_node_t * create_vector_node(void *data)
{
	vector_node_t *node = malloc(sizeof(vector_node_t));
	if(!node)
		return NULL;
	init_vector_node(node, data);
	
	return node;
}

void destroy_vector_node(vector_node_t *node)
{
	if(!node)
		return ;
	deinit_vector_node(node);
	free(node);

}

int vector_empty(vector_t *vector)
{
	if(vector->list.next == &vector->list)
		return 1;
	return 0;
//	int ret = list_empty(&vector->list);
//	printf("%s:%d ret = %d\n",__func__,__LINE__,ret);
//	return ret;
//	return list_empty(&vector->list);
}
