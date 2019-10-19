#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"
#include "node.h"
#include "store_node.h"

typedef struct stack_list{
	list_t	list;
}stack_t;

int init_stack(stack_t *stack);
void deinit_stack(stack_t *stack);


void stack_push(stack_t *stack, store_node_t *node);
store_node_t * stack_pop(stack_t *stack);

int stack_empty(stack_t *stack);



#endif
