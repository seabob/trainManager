#include <stdio.h>
#include <string.h>

#include "train_manager.h"

#include "list.h"

#define TEST_CASE_LENGTH	4

//Show all route and relation
static void print_routes(train_manager_t *train_manager)
{
    node_t *node = NULL;
    node_t *tmp_node = NULL;
    edge_t *edge = NULL;
    edge_t *tmp_edge = NULL;
    LIST_FOR_EACH_ENTRY_PREV_SAFE(node, tmp_node, &train_manager->graph.nodes,list)
    {
        printf("origin %c:\n",node->data);
        LIST_FOR_EACH_ENTRY_PREV_SAFE(edge, tmp_edge, &node->edges, list)
        {
            printf(" -- destination [%c]\n",edge->destination->data);
        }
    }
}

int main(int argv, char **argc)
{
    int index = -1;
    int distance = -1;
    char path[512] = {0};
    train_manager_t train_manager;
    char test_case[TEST_CASE_LENGTH] = {0};
    
    init_train_manager(&train_manager, argc[1]);

    while(get_testcase(&train_manager, test_case, TEST_CASE_LENGTH) > 0)
    {
	insert_route(&train_manager, test_case);
    }

#if 1
    print_routes(&train_manager);
#endif

   printf("\n*** Example: A-B-D-C ***\n\n");

   for(;;)
   {
       printf("input path:\n");
       memset(path,0,512);
       scanf("%s",path);

       if(strcmp(path,"quit") == 0)
           break;

    distance = get_calculate(&train_manager, path);
    if(distance != -1)
        printf("[%s]: %d\n", path,distance);
    else
        printf("[%s]: path fail\n",path);
    }

    deinit_train_manager(&train_manager);
    return 0;
}
