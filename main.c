#include <stdio.h>
#include <string.h>

#include "TrainManager.h"

#include "List.h"

int main(int argv, char **argc)
{
    int index;
    route_t *route = NULL;
    train_manager_t train_manager;   
    char *routes[] = {"AB5", "BC4", "CD8", "DC8", "DE6", "AD5", "CE2", "EB3", "AE7"};

    init_train_manager(&train_manager);

    for(index = 0; index < 9; index++)
    {
        insert_route(&train_manager, routes[index]);
    }

    {
	node_t *node = NULL;
	node_t *tmp = NULL;
	edge_t *edge = NULL;
	edge_t *temp = NULL;
	LIST_FOR_EACH_ENTRY_SAFE(node, tmp, &train_manager.graph.nodes,list){
		printf("origin %c:\n",node->data);
		LIST_FOR_EACH_ENTRY_SAFE(edge, temp, &node->edges, list){
			printf(" -- destination [%c]\n",edge->destination->data);
		}
    	}
    }

    printf("A-B-C: %d\n", get_distance(&train_manager, "A-B-C"));

    return 0;
}
