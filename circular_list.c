#include <stdlib.h>
#include <stdio.h>

#include "circular_list.h"
#include "list.h"
#include "node.h"

int init_circular(circular_t *circular)
{
	if(circular)
	{
		init_list(&circular->circular_list);
		return 0;
	}
	return -1;
}

void deinit_circular(circular_t *circular)
{
	if(!circular)
		return;

	node_t *node = NULL;
	node_t *node_tmp = NULL;
	
	LIST_FOR_EACH_ENTRY_SAFE(node, node_tmp, &circular->circular_list, circular_list)
	{
		if(node)
		{
			list_del(&node->circular_list);
		}
	}
	init_circular(circular);
}

void circular_add(circular_t *circular, node_t *node)
{
	node_t *ptr;
	if(circular && node)
	{
		printf("%s:%d node->circular_list = 0x%x, circular = 0x%x\n",__func__,__LINE__,&node->circular_list, &circular->circular_list);
		list_add(&node->circular_list, &circular->circular_list);
		printf("%s:%d data = %c\n",__func__,__LINE__,node->data);
		printf("%s:%d data = %c\n",__func__,__LINE__,node->data);
		printf("%s:%d data = %c\n",__func__,__LINE__,node->data);
	}
}

void circular_del(circular_t *circular, node_t *node)
{
	if(circular && node)
	{
	//	printf("%s:%d data = %c\n",__func__,__LINE__,node->data);
		list_del(&node->circular_list);
	}
}

void circular_add_list(circular_t *circular, list_t *list)
{
	if(circular && list)
		list_add(list, &circular->circular_list);
}

void circular_del_list(circular_t *circular, list_t *list)
{
	if(circular && list)
		list_del(list);
}

int circular_empty(circular_t *circular)
{
	return list_empty(&circular->circular_list);
}
