#include "core/edge.h"
#include <stdlib.h>

struct s_edge
{
    int node;
    float distance;
};

edge    *edge_new       (int node, float distance)
{
    edge *e = malloc(sizeof(edge));

    e->node = node;
    e->distance = distance;

    return e;
}

void    edge_free       (void *e)
{
    free((edge *)e);
}

int     edge_node       (edge *e)
{
    return e->node;
}

float   edge_distance   (edge *e)
{
    return e->distance;
}

void    edge_set_distance(edge *e, float distance)
{
    e->distance = distance;
}

void    edge_set_node(edge *e, int node)
{
    e->node = node;
}

