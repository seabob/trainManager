#include <stdio.h>
#include <string.h>

#include "train_manager.h"

#include "list.h"

#define TEST_CASE_LENGTH	4

static void print_usage(void)
{
	printf("\n*************************usage***********************************\n");
	printf("cmd [show/s]: show graph struction.\n");
	printf("cmd [help/h]: show this  usage.\n");
	printf("for quit to execute [quit] [exit] [q].\n");
	printf("\ncmd [distance]: calcular route distance.\n");
	printf("\tfor Example: distance ABC\n");
	printf("\ncmd [route]: calcular all route between param and limit by layer.\n");
	printf("\tfor Example: route CC 3\n");
	printf("\ncmd [trip]: calcular route with statin count between param and limit by layer,\n");
	printf("\tfor Example: trip AC 4\n");
	printf("\ncmd [short]: calcular shortest route distance by param\n");
	printf("\tfor Example: short BB\n");
	printf("\ncmd [allroute]: calcular all route station count by param\n");
	printf("\tfor Example: allroute CC 30\n\n");
	printf("\t\tformat:\n");
	printf("\t\t\t[cmd]  [param]  <layer>\n");
	printf("\t\t\troute     CC       3\n");
	printf("****************************************************************\n\n");
	
}

int main(int argv, char **argc)
{
    int distance = -1;
    char path[32] = {0};
    train_manager_t train_manager;
    char test_case[TEST_CASE_LENGTH] = {0};
    
    init_train_manager(&train_manager, argc[1]);

    while(get_testcase(&train_manager, test_case, TEST_CASE_LENGTH) > 0)
    {
	insert_route(&train_manager, test_case);
    }

#if 1
    print_usage();
#endif


   for(;;)
   {
        printf("input path:\n");
        memset(path,0,32);
	fgets(path, 32, stdin);
	path[strlen(path) - 1] = '\0';

        if(!strcmp(path,"quit") || !strcmp(path, "exit") || !strcmp(path, "q"))
	{
	    break;
	}
        else if(!strcmp(path, "show") || !strcmp(path, "s"))
	{
	    print_routes(&train_manager);
	    continue;
	}
	else if(!strcmp(path, "help") || !strcmp(path, "h"))
	{
	    print_usage();
	    continue;
	}else
	{
    	    distance = get_calculate(&train_manager, path);
            if(distance > 0)
                printf("[result]: %d\n", distance);
            else
                printf("[result]: NO SUCH ROUTE\n");
	}
    }

    deinit_train_manager(&train_manager);
    return 0;
}
