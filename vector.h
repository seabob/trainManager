#ifndef __VECTOT_H__
#define __VECTOR_H__

#include "list.h"
#include "node.h"
#include "store_node.h"

typedef struct vector_list{
	list_t	list;
}vector_t;

int init_vector(vector_t *vector);
void deinit_vector(vector_t *vector);

void vector_push(vector_t *vector, store_node_t *node);
store_node_t * vector_pop(vector_t *vector);

int vector_empty(vector_t *vector);



#endif
