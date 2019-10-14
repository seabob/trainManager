#include <stdlib.h>
#include <string.h>

#include "route.h"

static int __is_letter(char character)
{
    if(character >= 'a' && character <= 'z')
        return 0;
    else if(character >= 'A' && character <= 'Z')
        return 0;
    else
        return -1;
}

static int __is_number(char character)
{
    if(character >= '0' && character <= '9')
	return 0;
    return -1;
}

static int __check_raw_route(const char *raw_route)
{
    int ret = 0;
    ret += (strlen(raw_route) != 3);
    ret += __is_letter(raw_route[0]);
    ret += __is_letter(raw_route[1]);
    ret+ __is_number(raw_route[2]);

    return ret;
}

int init_route(route_t * route, const char *raw_route)
{
    if(__check_raw_route(raw_route) == -1)
        return -1;
    route->origin = raw_route[0];
    route->destination = raw_route[1];
    route->distance = raw_route[2] - '0';
    return 0;
}

route_t * create_route(const char *raw_route)
{
    route_t * __ptr_route = malloc(sizeof(route_t));
    if(__ptr_route == NULL)
        return NULL;

    return __ptr_route;
}

void destroy_route(route_t *__ptr_route)
{
    if(__ptr_route)
    {
        free(__ptr_route);
    }
}
