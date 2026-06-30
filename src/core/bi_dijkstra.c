#include "core/bi_dijkstra.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "core/heap.h"
#include "utils/logger.h"
#include <limits.h>
#include <stdlib.h>

static void __dijkstra_pass(
        graph *g, hashmap *visited, hashmap *opposite_visited, 
        edge *current,
        int s, int p,
        heap *remaining, 
        hashmap *results, hashmap *opposite_results,
        int *visited_node_number)
{
    LOG("Starting %d turn...", edge_node(current));
    // the node associated with the edge
    node    *current_node       = graph_get_edges(g, edge_node(current));
    
    // number of edges from current
    int     successors_number   = node_edge_number(current_node);
    // list of edges from current
    edge    **edge_list         = node_edge_list(current_node);

    hashmap_put(visited, edge_node(current), malloc(1));

    // iterate through all successors
    for (int i = 0; i < successors_number; i++)
    {
        if (hashmap_has(visited, edge_node(edge_list[i])))
        {
            LOG("  * Node (n:%d) already visited, skipping...", edge_node(edge_list[i]));
            continue;
        }

        (*visited_node_number)++;
        // current successor
        edge *successor     = edge_list[i]; 
        // successor but in result map
        edge *result        = hashmap_get(results, edge_node(edge_list[i]));

        float cumulative_distance = edge_distance(current) + edge_distance(successor);

        LOG("  * (%d->%d), edge distance: %f (relative:%f) (current in results: %f)", edge_node(current), edge_node(successor), cumulative_distance, edge_distance(successor), edge_distance(result));

        if (cumulative_distance < edge_distance(result))
        {  
            LOG("  * It's the best path, registering (s->%d: %f)", edge_node(successor), cumulative_distance);
            if (hashmap_has(opposite_results, edge_node(successor)))
            {
                edge *p_result          = hashmap_get(results, p);
                edge *backward_result   = hashmap_get(opposite_results, edge_node(successor));
                if (edge_distance(p_result) > cumulative_distance + edge_distance(backward_result))
                {
                    edge_set_distance(p_result, cumulative_distance + edge_distance(backward_result));
                }
            }
            heap_change_value(remaining, edge_node(successor), cumulative_distance);
            edge_set_node(result, edge_node(current));
            edge_set_distance(result, cumulative_distance);
        }
    }
}

hashmap     *bi_dijkstra(graph *g, int src, int dest, int *visited_node_number)
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

        hashmap_free(forward_results);
        hashmap_free(forward_visited);
        hashmap_free(backward_results);
        hashmap_free(backward_visited);

        free(nodes->inner);
        free(nodes);

        return NULL;
    }

    // && because if there's one empty heap, it means it has visited
    // all nodes. it should not happen anyway
    while (!heap_is_empty(remaining_forward_nodes) 
        && !heap_is_empty(remaining_backward_nodes))
    {
        // time to do it the normal way
        edge *forward       = heap_pop(remaining_forward_nodes);

        // break if it has already been visited in the opposite way
        if (hashmap_has(backward_visited, edge_node(forward)))
            break;

        hashmap_put(forward_visited, edge_node(forward), malloc(1));

        __dijkstra_pass(g, forward_visited, backward_visited, forward, src, dest, 
                remaining_forward_nodes, forward_results, backward_results, visited_node_number);

        // time to do it the opposite way
        edge *backward      = heap_pop(remaining_backward_nodes);

        if (hashmap_has(forward_visited, edge_node(backward)))
            break;

        hashmap_put(backward_visited, edge_node(backward), malloc(1));

        __dijkstra_pass(g, backward_visited, forward_visited, backward, dest, src, remaining_backward_nodes, backward_results, forward_results, visited_node_number);
    }

    hashmap_free(backward_results);
    hashmap_free(backward_visited);
    hashmap_free(forward_visited);
    heap_free(remaining_backward_nodes);
    heap_free(remaining_forward_nodes);
    free(nodes->inner);
    free(nodes);

    return forward_results;
}
