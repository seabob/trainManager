#ifndef __SEARCH_LIST_H__
#define __SEARCH_LIST_H__

#include "list.h"
#include "node.h"

typedef struct search_list{
	list_t	search_list;
}search_t;

int init_search(search_t *search);
void deinit_search(search_t *search);

void search_add(search_t *search, node_t *node);
void search_del(search_t *search, node_t *node);
void search_add_list(search_t *search, list_t *list);
void search_del_list(search_t *search, list_t *list);


#endif
