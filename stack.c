#include <stdlib.h>

#include "store_node.h"
#include "stack.h"
#include "list.h"

int init_stack(stack_t *stack)
{
	if(!stack)
		return -1;

	init_list(&stack->list);
	return 0;
}

void deinit_stack(stack_t *stack)
{
	init_stack(stack);
}

store_node_t * stack_top(stack_t *stack)
{
	return LIST_ENTRY(stack->list.next,store_node_t, list);
}

void stack_push(stack_t *stack, store_node_t  *node)
{
	if(stack && node)
	{
		list_add(&node->list, &stack->list);
	}
}

store_node_t* stack_pop(stack_t *stack)
{
	if(list_empty(&stack->list))
	{
		return NULL;
	}
	list_t *list = stack->list.next;
	store_node_t *node = LIST_ENTRY(list, store_node_t, list);
	list_del(list);
	return node;
}

int stack_empty(stack_t *stack)
{
	if(stack->list.next == &stack->list)
		return 1;
	return 0;
//	int ret = list_empty(&stack->list);
//	printf("%s:%d ret = %d\n",__func__,__LINE__,ret);
//	return ret;
//	return list_empty(&stack->list);
}
