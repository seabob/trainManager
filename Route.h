#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "List.h"

typedef struct route{
    char origin;
    char destination;
    int distance;
    list_t list;
}route_t;

int init_route(route_t *route, const char *raw_route);
route_t * create_route(const char *raw_route);
void destroy_route(route_t *__ptrroute);

#endif
