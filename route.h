#ifndef __ROUTE_H__
#define __ROUTE_H__

typedef struct route{
    char origin;
    char destination;
    int distance;
}route_t;

int init_route(route_t *route, const char *raw_route);
route_t * create_route(const char *raw_route);
void destroy_route(route_t *__ptrroute);

#endif
