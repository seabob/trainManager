#ifndef __TRAIN_MANAGER_H__
#define __TRAIN_MANAGER_H__

#include "graph.h"
#include "route_maker.h"
#include "graph_analyzer.h"
#include "file_reader.h"

#define TEST_CASE_FILE  "testfile.txt"

typedef struct train_manager{
    graph_t             graph;
    route_maker_t       route_maker;
    graph_analyzer_t    graph_analyzer;
    file_reader_t	reader;
}train_manager_t;


int init_train_manager(train_manager_t * train_manager, const char *testcase_file);
void deinit_train_manager(train_manager_t * train_manager);

train_manager_t *create_train_manager(const char *testcase_file);
void destroy_train_manager(train_manager_t *train_manager);

void insert_route(train_manager_t *train_manager, const char * route);
int get_distance(train_manager_t *train_manager, const char *path);

int get_testcase(train_manager_t *train_manager, char *test_case, size_t length);



#endif
