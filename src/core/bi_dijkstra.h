#include "core/bi_dijkstra.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "core/heap.h"
#include <limits.h>
#include <stdlib.h>


hashmap     *bi_dijkstra(graph *g, int src, int dest)
{
    int_list    *nodes                      = graph_get_all_nodes_names(g);
    int         n                           = nodes->size;

    heap        *remaining_forward_nodes    = heap_new(n);
    heap        *remaining_backward_nodes   = heap_new(n);

    bool        src_exists                  = false;
    bool        dest_exists                 = false;

    hashmap     *forward_visited            = hashmap_new(free);
    hashmap     *backward_visited           = hashmap_new(free);

    hashmap     *forward_results            = hashmap_new(edge_free);
    hashmap     *backward_results           = hashmap_new(edge_free);

    for (int i = 0; i < n; i++)
    {
        if      (nodes->inner[i] == src)
        {
            heap_insert(remaining_forward_nodes,  edge_new(src, 0.0));
            heap_insert(remaining_backward_nodes, edge_new(src, INT_MAX));
            hashmap_put(forward_results, src, edge_new(src, 0.0));
            hashmap_put(backward_results, src, edge_new(src, INT_MAX));
            src_exists = true;
        }
        else if (nodes->inner[i] == dest)
        {
            heap_insert(remaining_forward_nodes,  edge_new(dest, INT_MAX));
            heap_insert(remaining_backward_nodes, edge_new(dest, 0.0));
            hashmap_put(forward_results, dest, edge_new(dest, INT_MAX));
            hashmap_put(backward_results, dest, edge_new(dest, 0.0));
            dest_exists = true;
        }
        else
        {
            heap_insert(remaining_forward_nodes,  edge_new(nodes->inner[i], INT_MAX));
            heap_insert(remaining_backward_nodes, edge_new(nodes->inner[i], INT_MAX));
            hashmap_put(forward_results, nodes->inner[i], edge_new(dest, INT_MAX));
            hashmap_put(backward_results, nodes->inner[i], edge_new(dest, INT_MAX));
        }
    }

    if (!src_exists || !dest_exists) {
        heap_free(remaining_backward_nodes);
        heap_free(remaining_forward_nodes);
        
        free(nodes->inner);
        free(nodes);

        return NULL;
    }

    while (!heap_is_empty(remaining_forward_nodes) 
        || !heap_is_empty(remaining_backward_nodes))
    {
        edge *forward       = heap_pop(remaining_forward_nodes);
        edge *backward      = heap_pop(remaining_backward_nodes);

        // break if it has already been visited in the opposite way
        if (hashmap_has(backward_visited, edge_node(forward))
            || hashmap_has(forward_visited, edge_node(backward)))
            break;

        // TODO jsp 
    }
}
