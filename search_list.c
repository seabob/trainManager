#include "search_list.h"
#include "list.h"
#include "node.h"

int init_search(search_t *search)
{
	if(!search)
		return -1;

	init_list(&search->search_list);
	return 0;
}

void deinit_search(search_t *search)
{
	init_search(search);
}

void search_add(search_t *search, node_t *node)
{
	if(search && node)
	{
//		printf("%s:%d node->data = %c\n",__func__,__LINE__,node->data);
		list_add(&node->search_list, &search->search_list);
	}
}

void search_del(search_t *search, node_t *node)
{
	if(search && node)
	{
		list_del(&node->search_list);
	}
}
void search_add_list(search_t *search, list_t *list)
{
	if(search && list)
	{
		list_add(list, &search->search_list);
	}
}

void search_del_list(search_t *search, list_t *list)
{
	if(search && list)
	{
		list_del(list);
	}
}
