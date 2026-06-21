#include "core/graph.h"
#include "core/list.h"
#include "core/node.h"
#include "core/hashmap.h"
#include "utils/logger.h"
#include <stdlib.h>
#include <string.h>

struct s_graph
{
    hashmap     *storage;
    int         *node_names;
    size_t      node_number;

};

graph   *graph_new()
{
    graph *g = malloc(sizeof(struct s_graph));

    g->storage  = hashmap_new();
    g->node_number = 0;
    g->node_names = NULL;

    return g;
}

void    graph_free(graph *g)
{
    hashmap_free(g->storage);
    free(g);
}

int_list *graph_get_all_nodes_names(graph *g)
{
    int_list *lst = malloc(sizeof(int_list));
    
    memcpy(lst->inner, g->node_names, g->node_number * sizeof(int));
    lst->size = g->node_number;

    return lst;
}

void    graph_bulk_add_edge(graph *g, int src, int *dest, float *distance, size_t n)
{
    node *nd = hashmap_get(g->storage, src);

    if (nd == NULL)
    {
        g->node_number++;
        
        // to keep the names
        if (g->node_names != NULL) g->node_names = realloc(g->node_names, sizeof(g->node_number));
        else g->node_names = malloc(sizeof(int));
        g->node_names[g->node_number - 1] = src;
        LOG("Added node (%d) to the graph", src);

        nd = node_new();
        hashmap_put(g->storage, src, nd);
    }

    while (n-->0)
    {
        node_add_edge(nd, dest[n], distance[n]);
        LOG("Added edge from (%d) to (%d) (distance: %f)", src, dest[n], distance[n]);
    }
}

void    graph_add_edge(graph *g, int src, int dest, float distance)
{
    int dest_lst[1] = { dest };
    float distance_lst[1] = { distance };

    graph_bulk_add_edge(g, src, dest_lst, distance_lst, 1);
}

float   graph_get_distance(graph *g, int src, int dest)
{
    node *nd = hashmap_get(g->storage, src);

    if (nd != NULL)
    {
        return node_get_edge(nd, dest);
    }
    
    return -1.f;
}
