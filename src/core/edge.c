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

void    edge_free       (edge *e)
{
    free(e);
}

int     edge_node       (edge *e)
{
    return e->node;
}

float   edge_distance   (edge *e)
{
    return e->distance;
}



