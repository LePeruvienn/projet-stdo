#include "core/graph.h"
#include "core/edge.h"
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

    g->storage  = hashmap_new(node_free);
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

    lst->inner = malloc(sizeof(int) * g->node_number);

    for (int i = 0; i < g->node_number; i++)
        lst->inner[i] = g->node_names[i];

    lst->size = g->node_number;

    return lst;
}

static node *__graph_get_node_from_hashmap(graph *g, int node_name)
{
    node *nd = hashmap_get(g->storage, node_name);

    if (nd == NULL)
    {
        g->node_number++;

        // to keep the names
        if (g->node_names != NULL) g->node_names = realloc(g->node_names, sizeof(g->node_number));
        else g->node_names = malloc(sizeof(int));
        g->node_names[g->node_number - 1] = node_name;
        LOG("Added node (%d) to the graph", node_name);

        nd = node_new();
        hashmap_put(g->storage, node_name, nd);

    }

    return nd;
}

void    graph_bulk_add_edge(graph *g, int src, int *dest, float *distance, size_t n)
{
    node *nd = __graph_get_node_from_hashmap(g, src); 

    while (n-->0)
    {
        node *nd_dest = __graph_get_node_from_hashmap(g, dest[n]);
        node_add_edge(nd, dest[n], distance[n]);
        LOG("Added edge from (%d) to (%d) (distance: %f)", src, dest[n], distance[n]);
        node_add_edge(nd_dest, src, distance[n]);
        LOG("Added edge from (%d) to (%d) (distance: %f)", dest[n], src, distance[n]);
    }
}

int         graph_get_node_number(graph *g)
{
    return g->node_number;
}

void    graph_add_edge(graph *g, int src, int dest, float distance)
{
    int dest_lst[1] = { dest };
    float distance_lst[1] = { distance };

    graph_bulk_add_edge(g, src, dest_lst, distance_lst, 1);
}

edge   *graph_get_distance(graph *g, int src, int dest)
{
    node *nd = hashmap_get(g->storage, src);

    if (nd != NULL)
    {
        return edge_new(dest, node_get_edge(nd, dest));
    }
    
    return edge_new(dest, -1.f);
}

node    *graph_get_edges(graph *g, int src)
{
    return hashmap_get(g->storage, src);
}
