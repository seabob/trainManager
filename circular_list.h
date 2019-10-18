#ifndef __CICRULAR_H__
#define __CICRULAR_H__

#include "list.h"
#include "node.h"

typedef struct circular{
	list_t	circular_list; 
}circular_t;

int init_circular(circular_t *circular);
void deinit_circular(circular_t *circular);

void circular_add(circular_t *circular, node_t *node);
void circular_del(circular_t *circular, node_t *node);

void circular_add_list(circular_t *circular, list_t *list);
void circular_del_list(circular_t *circular, list_t *list);

int circular_empty(circular_t *circular);


#endif
