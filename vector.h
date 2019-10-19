#ifndef __VECTOT_H__
#define __VECTOR_H__

#include "list.h"
#include "node.h"

typedef struct vector_list{
	list_t	list;
}vector_t;

typedef struct vector_node_list{
	void	*data;
	list_t	list;
}vector_node_t;

int init_vector(vector_t *vector);
void deinit_vector(vector_t *vector);

int init_vector_node(vector_node_t *node, void * data);
void deinit_vector_node(vector_node_t *node);

vector_node_t * create_vector_node(void *data);
void destroy_vector_node(vector_node_t *node);

void vector_push(vector_t *vector, vector_node_t *node);
vector_node_t * vector_pop(vector_t *vector);

int vector_empty(vector_t *vector);



#endif
